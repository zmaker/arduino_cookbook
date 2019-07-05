#include <SoftwareSerial.h>

SoftwareSerial BTserial(6, 7); // RX | TX

#define __BAUD 38400

void setup(){
  BTserial.begin(__BAUD);
  delay(1000);
  Serial.println("ready...");
}

void loop() {  
  BTserial.write('a');
  delay(500);
  BTserial.write('s');
  delay(500);
 
}
