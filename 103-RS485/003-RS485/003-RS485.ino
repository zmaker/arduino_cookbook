/*
https://tecnicamente.wordpress.com/2012/04/07/arduino-max232-e-comunicazione-seriale-parte-1/
*/
#include <SoftwareSerial.h>

SoftwareSerial SSerial(11, 12); //12 RX e 11 TX

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(9600);
}

void loop() {
  if (SSerial.available()){
    Serial.write(SSerial.read());
  }
  if (Serial.available()){
    SSerial.write(Serial.read());
  }
}
