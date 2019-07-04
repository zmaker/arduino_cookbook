/*
 * https://www.adrirobot.it/Modulo_hc-05/modulo_hc-05.htm
https://www.lombardoandrea.com/arduino-hc-05-base/
*/

#include <SoftwareSerial.h>

SoftwareSerial BTserial(6, 7); // RX | TX
// Connect the HC-08 TX to Arduino pin 2 RX.
// Connect the HC-08 RX to Arduino pin 3 TX through a voltage divider.

#define __BAUD 38400

void setup(){
  Serial.begin(__BAUD);
  BTserial.begin(__BAUD);
  delay(1000);
  Serial.println("ready...");
}

void loop() {  
  if (BTserial.available()) {
    Serial.write(BTserial.read());
  }
  if (Serial.available()) {
    BTserial.write(Serial.read());
  }
}
