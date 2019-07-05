/*
 https://wiki.dfrobot.com/DF-BluetoothV3_Bluetooth_module__SKU_TEL0026_    
*/

#include <SoftwareSerial.h>

SoftwareSerial BTserial(6, 7); // RX | TX
// Connect the HC-08 TX to Arduino pin 2 RX.
// Connect the HC-08 RX to Arduino pin 3 TX through a voltage divider.

#define __BAUD 38400

void setup(){
  Serial.begin(9600);
  BTserial.begin(9600);
  delay(1000);
  Serial.println("ready...");
  pinMode(13, OUTPUT);
}

void loop() {  
  if (BTserial.available()) {
    char c = BTserial.read();
    Serial.write(c);
    if (c == 'a') {
      digitalWrite(13, HIGH);
    }
    if (c == 's') {
      digitalWrite(13, LOW);
    }
  }
}
