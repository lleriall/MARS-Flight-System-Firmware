window.addEventListener("gamepadconnected", (event) => {
    handleConnectDisconnect(event, true);
});
  
window.addEventListener("gamepaddisconnected", (event) => {
    handleConnectDisconnect(event, false);
});

function handleConnectDisconnect(event, connected){
    
}