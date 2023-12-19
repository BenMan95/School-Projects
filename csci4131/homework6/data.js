// this package behaves just like the mysql one, but uses async await instead of callbacks.
const mysql = require(`mysql-await`); // npm install mysql-await

// first -- I want a connection pool: https://www.npmjs.com/package/mysql#pooling-connections
// this is used a bit differently, but I think it's just better -- especially if server is doing heavy work.
var connPool = mysql.createPool({
  connectionLimit: 5, // it's a shared resource, let's not go nuts.
  host: <host>,// this will work
  user: <user>,
  database: <database>,
  password: <password>, // we really shouldn't be saving this here long-term -- and I probably shouldn't be sharing it with you...
});

// later you can use connPool.awaitQuery(query, data) -- it will return a promise for the query results.

async function addContact(data){
  connPool.awaitQuery(`INSERT INTO contact (cname, email, mdate, meeting, soul)
                       VALUES (?, ?, ?, ?, ?)`,
                       [data.name, data.email, data.date, data.meeting, Boolean(data.soul)])
}

async function deleteContact(id){
  result = await connPool.awaitQuery(`DELETE FROM contact
                                      WHERE ID=?`, [id])
  return result.affectedRows != 0
}

async function getContacts() {
  return connPool.awaitQuery('SELECT * FROM contact')
}

async function addSale(message) {
  connPool.awaitQuery(`INSERT INTO sale (sale_text)
                       VALUES (?)`, [[message]])
}

async function endSales() {
  connPool.awaitQuery(`UPDATE sale
                       SET time_end=CURRENT_TIMESTAMP
                       WHERE time_end IS NULL`)
}

async function getRecentSales() {
  return connPool.awaitQuery(`SELECT * FROM sale
                              ORDER BY time_start DESC
                              LIMIT 3`)

}

module.exports = {addContact, getContacts, deleteContact, addSale, endSales, getRecentSales}