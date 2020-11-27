const  {Board, Led, Sensor} = require("johnny-five");
const board = new Board();

board.on("ready", function() {
  const sensor = new Sensor("A1");
  const led = new Led(11);

  sensor.on("data", function(){
      led.brightness(sensor.scaleTo([0,255]));
  });
});