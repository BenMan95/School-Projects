const tbody = document.getElementsByTagName("tbody")[0];
const message = document.getElementById("message");

function setMessage(msg, time) {
    message.textContent = msg;
    message.hidden = false;
    setTimeout(() => message.hidden = true, time);
}

function formatTime(millis) {
    let seconds = Math.floor(millis / 1000);
    let minutes = Math.floor(seconds / 60);
    seconds %= 60;

    let hours = Math.floor(minutes / 60);
    minutes %= 60;

    let days = Math.floor(hours / 24);
    hours %= 24;

    if (days > 0) {
        return `${days} days, ${hours} hours, ${minutes} minutes, ${seconds} seconds`;
    }

    if (hours > 0) {
        return `${hours} hours, ${minutes} minutes, ${seconds} seconds`;
    }

    if (minutes > 0) {
        return `${minutes} minutes, ${seconds} seconds`;
    }

    return `${seconds} seconds`;
}

for (let row of tbody.children) {
    let dateEle = row.getElementsByClassName("date")[0];
    let msgEle = row.getElementsByClassName("time")[0];
    let buttonEle = row.getElementsByTagName("button")[0];

    function updateTime() {
        if (dateEle.textContent) {
            // Set remaining time if date set
            let aptTime = Date.parse(dateEle.textContent);
            let curTime = new Date().getTime();

            // Set default message to PASSED
            let msg = "PASSED";

            // If is current time is before appointment, change message to remaining time
            if (curTime < aptTime) {
                let millis = aptTime - curTime;
                msg = formatTime(millis) + " left";
            }

            // Set message text
            msgEle.textContent = " \u2014 " + msg;
        } else {
            // Set message if no date set
            msgEle.textContent = "No date set";
        }
    }

    // Initialize and set timer to update every second
    updateTime();
    let interval = setInterval(updateTime, 1000);

    async function removeRow() {
        // Make request to server
        let id = parseInt(buttonEle.getAttribute('data-id'));
        let response = await fetch('/api/contact', {
            method: 'DELETE',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({id})
        });

        // Remove table element if status is 200 or 404
        if (response.status == 200 || response.status == 404) {
            clearInterval(interval);
            tbody.removeChild(row);
            setMessage('Contact successfully removed', 3000);
        } else {
            setMessage('Error removing contact', 3000);
        }
    }

    // Set button event to clear interval and remove row
    buttonEle.addEventListener("click", removeRow);
}

const msgInput = document.getElementById("msg");
const setButton = document.getElementById("set");
const deleteButton = document.getElementById("delete");

async function setSale(event) {
    event.preventDefault();

    let msgBody = {"message": msgInput.value};

    let result = await fetch('/api/sale', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify(msgBody)
    });

    if (result.ok)
        setMessage('Sale successfully set', 3000);
    else
        setMessage('Error setting sale', 3000);
}

async function deleteSale(event) {
    event.preventDefault();
    let result = await fetch('/api/sale', {method: 'DELETE'});
    if (result.ok)
        setMessage('Sales successfully removed', 3000);
    else
        setMessage('Error removing sale', 3000);
}

setButton.addEventListener("click", setSale);
deleteButton.addEventListener("click", deleteSale);
