#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);  // High speed I2C

const byte alien[8] PROGMEM = {
  B00011000,
  B01111110,
  B01011010,
  B11011011,
  B11111111,
  B00101010,
  B00101010,
  B01010100,
};

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawXBMP(40,20, 8,8, alien);
  u8g2.sendBuffer();
  delay(100);
}
