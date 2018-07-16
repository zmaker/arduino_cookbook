#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("ok");
}

void loop() {
  Wire.requestFrom(7, 12);
  while (Wire.available()){
    char c = Wire.read();
    Serial.println(c);
  }
  delay(500);
}
