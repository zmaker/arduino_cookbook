/**
 https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/wiring-and-test
 */
#include <Wire.h>
#include <U8x8lib.h>

#define TCAADDR 0x70 
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

U8X8_SSD1306_128X64_ALT0_HW_I2C display1(/* reset=*/ U8X8_PIN_NONE); 
U8X8_SSD1306_128X64_ALT0_HW_I2C display2(/* reset=*/ U8X8_PIN_NONE); 

void setup() {
  Serial.begin(9600);
  tcaselect(1);
  display1.begin();
  display1.setPowerSave(0);
  display1.setFont(u8x8_font_chroma48medium8_r);
  
  tcaselect(2);
  display2.begin();
  display2.setPowerSave(0);
  display2.setFont(u8x8_font_chroma48medium8_r);
}

void loop() {
  tcaselect(1);
  display1.drawString(0,0,"Hello World 1!"); 
  display1.refreshDisplay();    
  
  tcaselect(2);
  display2.drawString(0,0,"Hello World 2!");  
  display2.refreshDisplay();    

  delay(1000);

}
