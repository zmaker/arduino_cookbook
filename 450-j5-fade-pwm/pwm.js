const {Board, Led} = require("johnny-five");
const board = new Board();

board.on("ready", function(){
  const led = new Led(11);
  led.pulse();
  board.wait(10000, () => {
      led.stop().off();
  });
    
});