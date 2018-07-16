#include <Wire.h>

void setup() {
  Wire.begin();
}

int i = 0;

void loop() {
  Wire.beginTransmission(7);
  Wire.write(i);
  Wire.endTransmission();  
  i++;
  delay(500);
}
