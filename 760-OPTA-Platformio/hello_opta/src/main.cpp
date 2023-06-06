#include <Arduino.h>

void setup() {
  pinMode(BTN_USER, INPUT);
  pinMode(LED_D0, OUTPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  int bt = !digitalRead(BTN_USER);
  if (bt) {
    digitalWrite(LED_D0, HIGH);
    digitalWrite(D0, HIGH);
  } else {
    digitalWrite(LED_D0, LOW);
    digitalWrite(D0, LOW);
  }
}
