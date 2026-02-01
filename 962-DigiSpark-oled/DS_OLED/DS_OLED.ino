#include <DigisparkOLED.h>
#include <Wire.h>

void setup() {
  oled.begin();

  oled.fill(0xFF);
  delay(1000);
  oled.clear();
  delay(1000);
}

void loop() {
  oled.setCursor(1,1);
  oled.setFont(FONT8X16);
  oled.print(F("HelloDS"));
  delay(2000);
}
