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

// initial position of the point is the middle of the screen
// initial position of the point is the middle of the screen
int xPos = 80;
int yPos = 64;

// direction and speed
int xDir = 1;
int yDir = 1;

// variables to keep track of the point's location
int xPrev = xPos;
int yPrev = yPos;

void setup(){
  myScreen.begin();  
  myScreen.background(0,0,0); // clear the screen
}

void loop(){
  // update the location of the dot
  xPos = xPos + xDir;
  yPos = yPos + yDir;

  // check if the current location is different than the previous
  if(xPos != xPrev || yPos != yPrev){
    myScreen.stroke(0,0,0); // set the stroke color to black 
    myScreen.fill(0,0,0);
    //myScreen.point(xPrev, yPrev); // color in the previous point 
    myScreen.rect(xPrev, yPrev, 10,10);
  }

  // draw a point in the current location
  myScreen.stroke(255,255,255);
  myScreen.fill(255,255,255);
  //myScreen.point(xPos, yPos);
  myScreen.rect(xPos, yPos, 10,10);

  // if the x or x position is at the screen edges, reverse direction
  if(xPos >= 160-10 || xPos <= 0){
    xDir = xDir*-1;
  }
  if(yPos >= 128-10 || yPos <= 0){
    yDir = yDir*-1;
  }

  // update the point's previous location
  xPrev=xPos;
  yPrev=yPos;

  // a 33ms delay means the screen updates 30 times a second
  delay(33);

}
