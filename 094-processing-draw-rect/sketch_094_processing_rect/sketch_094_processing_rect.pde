import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int ledPin = 13;

void setup() {
  //println(Serial.list()[0]);  
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[2], 57600);
  arduino.pinMode(ledPin, Arduino.OUTPUT);
  
  size(700,500);
  background(0);
  stroke(255);
  fill(255);
}

int x = 350;
int y = 250;

void draw() {
  int dx = arduino.analogRead(0);
  int dy = arduino.analogRead(1);
  dx = (int)map(dx, 0, 1023, -10, 10);
  dy = (int)map(dy, 0, 1023, -10, 10);
  
  x = x + dx;
  y = y + dy;
  
  rect(x,y, 10,10);
  //background(0);  
}