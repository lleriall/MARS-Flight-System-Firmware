var currentPage = 1;

document.getElementById("emi-select").addEventListener("click", function () {
    utilitySwitcher(4);
});

document.getElementById("actions-select").addEventListener("click", function () {
    utilitySwitcher(2);
});

document.getElementById("logs-select").addEventListener("click", function () {
    utilitySwitcher(3);
});

document.getElementById("stats-select").addEventListener("click", function () {
    utilitySwitcher(1);
});

document.getElementById("emi-mpopup").addEventListener("click", function () {
    var menu = document.getElementById("ECV-menu");
    menu.style.visibility = "visible";
});

document.getElementById("ECV-menu-close").addEventListener("click", function () {
    var closemenu = document.getElementById("ECV-menu");
    closemenu.style.visibility = "hidden";
});

function hideStatsMenu(){
    var smnu = document.getElementById("initStat-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showStatsMenu(){
    var smnu = document.getElementById("initStat-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideActionsMenu(){
    var smnu = document.getElementById("actions-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showActionsMenu(){
    var smnu = document.getElementById("actions-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideLogsMenu(){
    var smnu = document.getElementById("mainTelem-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showLogsMenu(){
    var smnu = document.getElementById("mainTelem-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideEMIMenu(){
    var smnu = document.getElementById("emi-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showEMIMenu(){
    var smnu = document.getElementById("emi-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function utilitySwitcher(pageFlag){
    /*
        1 -> Stats Menu
        2 -> Actions Menu
        3 -> Logs Menu
        4 -> EMI Menu
    */
   //Hide previous page
   switch(currentPage){
    case 1:
        hideStatsMenu();
        document.getElementById("stats-select").className = "nonactive";
        break;
    case 2:
        hideActionsMenu();
        document.getElementById("actions-select").className = "nonactive";
        break;
    case 3:
        hideLogsMenu();
        document.getElementById("logs-select").className = "nonactive";
        break;
    case 4:
        hideEMIMenu();
        document.getElementById("emi-select").className = "nonactive";
        break;
}
   //Switch current page flag
    switch(pageFlag){
        case 1:
            showStatsMenu();
            document.getElementById("stats-select").className = "active";
            break;
        case 2:
            showActionsMenu();
            document.getElementById("actions-select").className = "active";
            break;
        case 3:
            showLogsMenu();
            document.getElementById("logs-select").className = "active";
            break;
        case 4:
            showEMIMenu();
            document.getElementById("emi-select").className = "active";
            break;
    }
    //Set new current page
    currentPage = pageFlag;
}

