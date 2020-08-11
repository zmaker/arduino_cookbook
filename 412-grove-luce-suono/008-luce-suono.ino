#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setDrawColor(1);
  
  u8g2.setFlipMode(1);

  u8g2.setFontRefHeightExtendedText();  
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

int luce = 0, suono = 0;

void loop() {
  luce = analogRead(A6);
  suono = analogRead(A2);
  
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  delay(100);
}

void draw() {  
  u8g2.drawStr(0,0, "L:");
  u8g2.drawBox(11,0, map(luce, 0, 1024, 11, 128),10);  
  u8g2.drawStr(0,20, "S:");
  u8g2.drawBox(11,20, map(suono, 0, 1024, 11, 128),10);  
}
