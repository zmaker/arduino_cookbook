var five = require("johnny-five");
var arduino = new five.Board();

//la porta si può anche specificare:
/*
const board = new Board({
  port: "/dev/cu.usbmodem1411"
});
*/

arduino.on("ready", function() {
    
    arduino.pinMode(13, arduino.MODES.OUTPUT);
    
    
    
    arduino.loop(1000, () => {
        arduino.digitalWrite(13, arduino.pins[13].value ? 0 : 1);
    });
})
