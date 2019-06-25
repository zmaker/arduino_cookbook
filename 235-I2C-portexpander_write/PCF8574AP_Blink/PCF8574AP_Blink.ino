#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  Serial.println("ok");
}

void loop() {
  Wire.beginTransmission(0x38);
  Wire.write((byte)0b11111111);
  Wire.endTransmission();

  delay(500);

  Wire.beginTransmission(0x38);
  Wire.write((byte)0b00000000);
  Wire.endTransmission();

  delay(500);

}
