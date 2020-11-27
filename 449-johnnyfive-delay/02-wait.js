var five = require("johnny-five");
var arduino = new five.Board();

//la porta si può anche specificare:
/*
const board = new Board({
  port: "/dev/cu.usbmodem1411"
});
*/

arduino.on("ready", function() {
    
    arduino.pinMode(12, arduino.MODES.OUTPUT);
    
    arduino.digitalWrite(12, 1);
    arduino.wait(2000, function() {
      // Turn it off...
      arduino.digitalWrite(12, 0);
    });
    
})
