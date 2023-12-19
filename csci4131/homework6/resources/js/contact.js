const meetingEle = document.getElementById("meeting");
const soulEle = document.getElementById("soul");
const outputEle = document.getElementById("output");

function update() {
    // The fee is 0 if they forfeit their soul
    // Otherwise it is $5 for online or $10 for in person
    let value = 0;
    if (!soulEle.checked) {
        if (meetingEle.value == "Online") {
            value = 5;
        } else {
            value = 10;
        }
    }
    outputEle.textContent = "Fee: $" + value;
}

meetingEle.addEventListener("input", update);
soulEle.addEventListener("change", update);
update();
