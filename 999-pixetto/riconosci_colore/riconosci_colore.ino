#include <Arduino.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); 

#include <SmartSensor.h>
SmartSensor ss(7, 8);  //RX, TX

void setup() {
  ss.begin();
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

char buf[4];

void loop() {
  if (ss.isDetected()) {
    int x = ss.getPosX() + ss.getWidth() / 2;
    int y = ss.getPosY() + ss.getHeight() / 2;

    sprintf(buf, "%03i", x);
    u8x8.drawString(0, 1, "x:");
    u8x8.drawString(2, 1, buf);

    sprintf(buf, "%03i", y);
    u8x8.drawString(6, 1, "y:");
    u8x8.drawString(8, 1, buf);
    
    if (ss.getFuncID() == ss.FUNC_COLOR_DETECTION) {
      if (ss.getTypeID() == ss.COLOR_RED) {
         u8x8.drawString(0, 0, "RED  ");
      } else if (ss.getTypeID() == ss.COLOR_BLUE) {
         u8x8.drawString(0, 0, "BLUE ");
      } else if (ss.getTypeID() == ss.COLOR_GREEN) {
         u8x8.drawString(0, 0, "GREEN");
      } 
    }
  }
  u8x8.refreshDisplay();
  delay(100);
}
