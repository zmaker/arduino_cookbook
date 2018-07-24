import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int ledPin = 13;

void setup() {
  //println(Serial.list()[0]);  
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[2], 57600);
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

void draw() {
  arduino.digitalWrite(ledPin, Arduino.HIGH);
  delay(100);
  arduino.digitalWrite(ledPin, Arduino.LOW);
  delay(100);
}