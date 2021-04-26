/**
 * Seeeduino XIAO
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);         

void setup() {
  u8x8.begin();    
  u8x8.setFlipMode(1);
  //font: https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_8x13B_1x2_f);  
}

int count = 0;
char str[10];

void loop() {
  count++;
  u8x8.drawString(0,0,"Hello World!");
  u8x8.drawString(0,3,itoa(count, str, 6));
  u8x8.refreshDisplay();
  delay(500);
}
