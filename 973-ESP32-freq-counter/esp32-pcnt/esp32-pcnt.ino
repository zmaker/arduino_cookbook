/*
https://github.com/serena-ramley/ESP32-PCNT
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html
*/

#include "my-pcnt.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  int16_t count = 0;
  pcnt_init_and_start();
  delay(100);
  pcnt_get(&count);
  Serial.println(count);
  pcnt_clear();
}
