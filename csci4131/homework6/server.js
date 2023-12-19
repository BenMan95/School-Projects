const express = require('express')
const basicAuth = require('express-basic-auth')
const data = require('./data.js')
const app = express()
const port = 4131

// Checks if a sale time string is in the past
function sale_time_past(date) {
    if (date == null)
        return false
    return Date.parse(date) < Date.now()
}

app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})

// Set up Pug engine
app.set('views', 'templates')
app.set('view engine', 'pug')

// Set up middleware for static content and parsing data
app.use('/', express.static('resources'))
app.use(express.urlencoded({extended: true}))
app.use(express.json())

// Create middleware function for authentication
let authFunc = basicAuth({
    users: {'admin':'password'},
    challenge: true
})

// Handle most GET requests
app.get(['/', '/main'], (req, res) => res.render('mainpage'))
app.get('/testimonies', (req, res) => res.render('testimonies'))
app.get('/contact',     (req, res) => res.render('contactform'))

app.get('/admin/contactlog', authFunc, async (req, res) => {
    let contacts = await data.getContacts()
    res.render('contactlog', {contacts})
})
app.get('/admin/salelog', authFunc, async (req, res) => {
    let out = []
    let sales = await data.getRecentSales()
    for (let sale of sales) {
        out.push({
            message: sale.sale_text,
            active: sale_time_past(sale.time_end) ? 0 : 1
        })
    }
    res.send(out)
})

function paramsValid(params) {
    // Check fields present
    if (!Object.hasOwn(params, 'name'))
        return false
    if (!Object.hasOwn(params, 'email'))
        return false
    if (!Object.hasOwn(params, 'date'))
        return false
    if (!Object.hasOwn(params, 'meeting'))
        return false

    // Email format checking has been left as an exercise for the user (and the browser)

    // Check valid meeting type
    if (params.meeting != 'Online' && params.meeting != 'In Person')
        return false

    // Check valid meeting date
    if (!/^(\d{4}-\d{2}-\d{2})?$/.test(params.date))
        return false

    return true
}

// Handle adding contacts
app.post('/contact', async (req, res) => {
    if (paramsValid(req.body)) {
        await data.addContact(req.body)
        res.status(201)
        res.render('formmessage', {message: "Your appointment has been scheduled."})
    } else {
        res.status(400)
        res.render('formmessage', {message: "There was an error with your request."})
    }
})

// Handle deleting contacts
app.delete('/api/contact', authFunc, async (req, res) => {
    if (!Object.hasOwn(req.body, 'id')) {
        res.status(400)
        res.set('Content-Type', 'text/plain')
        res.send('Request must include ID of entry to delete')
        return
    }

    let result = await data.deleteContact(req.body.id)
    if (result) {
        res.status(200)
        res.set('Content-Type', 'text/plain')
        res.send('Entry successfully deleted')
    } else {
        res.status(404)
        res.set('Content-Type', 'text/plain')
        res.send('Entry does not exist')
    }
})

// Handle sale API
app.get('/api/sale', async (req, res) => {
    res.status(200)
    res.set('Content-Type', 'application/json')

    let sales = await data.getRecentSales()
    if (sales.length == 0 || sale_time_past(sales[0].time_end)) {
        res.send({
            active: false,
            message: null,
        })
    } else {
        res.send({
            active: true,
            message: sales[0].sale_text
        })
    }
})
app.post('/api/sale', authFunc, (req, res) => {
    if (!Object.hasOwn(req.body, 'message')) {
        res.status(400)
        res.set('Content-Type', 'text/plain')
        res.send('Error processing request')
        return
    }

    data.addSale(req.body.message)

    res.status(200)
    res.set('Content-Type', 'text/plain')
    res.send('Sale successfully updated')
})
app.delete('/api/sale', authFunc, (req, res) => {
    data.endSales()

    res.status(200)
    res.set('Content-Type', 'text/plain')
    res.send('Sale successfully removed')
})

// Handle 404 errors here
app.use((req, res, next) => {
    res.status(404)
    res.render('404')
    next()
})