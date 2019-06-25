#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  Serial.println("ok");
}

void loop() {
  Wire.requestFrom(0x38,1);
  if (Wire.available()) {
    byte b = Wire.read();
    Serial.println(b, BIN); 
  }
  delay(1000);
}
