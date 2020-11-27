const {Board, Led} = require("johnny-five");
const board = new Board();

board.on("ready", function(){
  const led = new Led(11);
    
  led.fadeIn();
  board.wait(3000, () => {
      led.fadeOut();
  });
    
});