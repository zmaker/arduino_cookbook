#include <TFT.h> // Hardware-specific library
#include <SPI.h>

#define CS   10
#define DC   9
#define RESET  8  

// pin definition for the Leonardo
// #define CS   7
// #define DC   0
// #define RESET  1 

TFT myScreen = TFT(CS, DC, RESET);

void setup(){
  myScreen.begin();  
  myScreen.background(0,0,0);  // clear the screen with black
  delay(1000);  // pause for dramatic effect
}

void loop(){
  myScreen.stroke(255, 0, 0); // set the stroke color to red
  myScreen.line(0, 10, myScreen.width(), 10); // draw a line across the screen
  delay(1000);

  myScreen.noStroke(); // don't draw a line around the next rectangle
  myScreen.fill(0,255,0); // set the fill color to green
  myScreen.rect(0,20,myScreen.width(),10); //draw a rectangle across the screen
  delay(1000);

  myScreen.fill(0,0,255); // set the fill color to blue
  myScreen.stroke(255,255,255); // outline the rectangle with a white line
  myScreen.rect(0,45,myScreen.width(),45); // draw a fat rectangle
  delay(1000);

  myScreen.background(0,0,0); // clear the screen before starting again
  delay(1000); 
}
