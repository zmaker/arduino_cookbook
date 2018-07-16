#include <Wire.h>

void setup() {
  Wire.begin(7);  
  Wire.onReceive(riceviDati);
  Serial.begin(9600);
}

void loop() { }

void riceviDati() {
  int x = Wire.read();
  Serial.println(x);
}
