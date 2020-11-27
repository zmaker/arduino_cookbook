var five = require("johnny-five");

var arduino = new five.Board();

arduino.on("ready", function() {
  var led = new five.Led(13);
  led.blink(500);    
});
