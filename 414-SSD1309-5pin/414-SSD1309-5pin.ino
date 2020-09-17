#include <U8x8lib.h>
#include <Wire.h>

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(U8X8_PIN_NONE); 

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  u8x8.begin();
  //u8x8.setFlipMode(1);
}

void loop() {
  u8x8.setFont(u8x8_font_5x7_f);
  u8x8.setCursor(0,0);
  u8x8.print("Hello World");
  delay(1000);
}
