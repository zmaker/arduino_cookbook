#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

void setup(void) {
  u8g.begin();
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}

void draw() {
  u8g.drawLine(0, 0, 20, 20);  
  u8g.drawBox(30,0,20,20);
  u8g.drawFrame(0,30,20,20);
  u8g.drawDisc(60,20,10);
  u8g.drawCircle(60,40,10);
}
