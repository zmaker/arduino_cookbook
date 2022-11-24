#include "BluetoothSerial.h"
#include <SimpleDHT.h>

BluetoothSerial bt;
SimpleDHT22 dht22(15);
unsigned long t1;

void setup() {
  Serial.begin(115200);
  delay(1000);  
  bt.begin("ESP32-BT1");
  Serial.println("ESP32 DHT22");
}

void loop() {
  if ((millis() - t1) >= 3000) {
    float temp = 0.0;
    float hum = 0.0;
    dht22.read2(&temp, &hum, NULL);
    String msg = "t: " + String(temp) + "C h:" + String(hum) + "%";
    bt.println(msg);
    t1 = millis();
  }
}
