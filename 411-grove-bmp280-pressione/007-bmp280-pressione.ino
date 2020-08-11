#include <U8x8lib.h>
#include "Seeed_BMP280.h"

BMP280 bmp280;

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

void setup(void) {
  bmp280.init();
  
  u8x8.begin();
  u8x8.setFlipMode(1);
} 

void loop(void) {     
  // font list: https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_5x7_f  /*u8x8_font_chroma48medium8_r*/);   
  u8x8.setCursor(0, 0);   
  u8x8.print("t:");
  u8x8.print(bmp280.getTemperature());        
  u8x8.print(" C");

  float pressione = bmp280.getPressure();
  u8x8.setCursor(0, 1);   
  u8x8.print("P:");
  u8x8.print(pressione);        
  u8x8.print(" Pa");

  u8x8.setCursor(0, 2);   
  u8x8.print("h:");
  u8x8.print(bmp280.calcAltitude(pressione));        
  u8x8.print(" m");
  
  delay(2000);  
}
