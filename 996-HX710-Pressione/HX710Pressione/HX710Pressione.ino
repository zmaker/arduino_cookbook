// https://github.com/bogde/HX711
#include "HX711.h"

const int DOUT_PIN = 4;
const int SCK_PIN = 5;

HX711 adc;

void setup() {
  Serial.begin(115200);
  adc.begin(DOUT_PIN, SCK_PIN);
}

void loop() {
  if (adc.is_ready()) {
    long press = adc.read();
    Serial.println(press);
  }
  delay(100);
}
