#include "test.h"

void setup() {
  int n = hello();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  sayHello(&Serial);
}
