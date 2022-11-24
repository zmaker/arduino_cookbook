#include "BluetoothSerial.h"

BluetoothSerial bt;

void setup() {
  Serial.begin(115200);  
  delay(1000);
  Serial.println("ESP32 BT Test - Console");

  bt.begin("ESP32-BT1");
}

void loop() {
  if (Serial.available()) {
    bt.write(Serial.read());
  }
  if (bt.available()) {
    Serial.write(bt.read());
  }
  delay(20);
}
