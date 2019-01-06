#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

int i = 0;

void loop() {
  Serial.println(i);
  i++;
  delay(500);
}
