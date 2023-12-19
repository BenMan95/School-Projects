const stylesheetEle = document.getElementsByTagName("link")[0]

function toggle_style() {
    let currTheme = localStorage.getItem("theme");
    let newTheme;

    if (currTheme == "/css/main.dark.css") {
        newTheme = "/css/main.css";
    } else {
        newTheme = "/css/main.dark.css";
    }

    localStorage.setItem("theme", newTheme);
    stylesheetEle.href = newTheme;
}

let button = document.getElementById("theme-button");
if (button) {
    button.addEventListener("click", toggle_style);
}

let currTheme = localStorage.getItem("theme");
if (currTheme) {
    document.getElementsByTagName("link")[0].href = currTheme;
}