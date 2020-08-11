#include <U8x8lib.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

void setup(void) {
  //Wire.begin();
  dht.begin();
  u8x8.begin();
  u8x8.setFlipMode(1);
} 

float dati[2] = {0.0, 0.0};

void loop(void) {     
  if(!dht.readTempAndHumidity(dati)) {
    // font list: https://github.com/olikraus/u8g2/wiki/fntlist8x8
    u8x8.setFont(u8x8_font_5x7_f  /*u8x8_font_chroma48medium8_r*/);   
    u8x8.setCursor(0, 0);   
    u8x8.print("t:");
    u8x8.print(dati[1]);        
    u8x8.print(" C");
    u8x8.setCursor(0, 1);   
    u8x8.print("h:");
    u8x8.print(dati[0]);        
    u8x8.print(" %");
  }
  delay(2000);  
}
