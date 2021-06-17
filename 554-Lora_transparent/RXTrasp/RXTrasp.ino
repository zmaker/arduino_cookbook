#include "Arduino.h"
#include "LoRa_E32.h"
 
SoftwareSerial mySerial(3, 2); // e32 TX e32 RX
 
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
    
  Serial.println("RX!");  
}
 
void loop() {
  if (mySerial.available()) {
    int n = mySerial.read();
    digitalWrite(13, n);
    Serial.write(n);
  }
  
}
