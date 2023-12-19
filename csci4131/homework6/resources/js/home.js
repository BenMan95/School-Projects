const message = document.getElementById("message");

async function updateMessage() {
    let response = await fetch('/api/sale')
    if (response.ok) {
        let json = await response.json();
        message.hidden = !json.active;
        if (json.active)
            message.textContent = json.message;
    }
}

setInterval(updateMessage, 1000);