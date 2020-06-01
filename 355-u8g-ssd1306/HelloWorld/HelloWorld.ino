#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send AC
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void setup(void) {
  u8g.begin();
  Serial.begin(9600);
  // flip screen, if required
  //u8g.setRot180();
  //u8g.setRot90();
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
    Serial.println(".");
  } while( u8g.nextPage() );
}

void draw() {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}
