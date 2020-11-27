var five = require("johnny-five");
var board = new five.Board();

board.on("ready", function(){    
    var button = new five.Button(2);
    
    button.on("press", function(){
        console.log("premuto");
    });
    button.on("release", function(){
        console.log("rilasciato");
    });
    button.on("hold", function(){
        console.log("hold");
    });
});