#include "Arduino.h"
#include "LoRa_E32.h"
 
SoftwareSerial mySerial(3, 2); // e32 TX e32 RX
 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  delay(500);

  //Factory reset - MO e M1 su H
  byte buf[] = { 0xC0, 0x00, 0x00, 0x1A, 0x06, 0x44 };
  mySerial.write((uint8_t *)buf, 6);
  delay(500);
    
  Serial.println("RX!");  
}
 
void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }
  
}
