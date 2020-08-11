#include <U8x8lib.h>
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

#include <Wire.h>
#include "LIS3DHTR.h"

LIS3DHTR<TwoWire> LIS;
#define WIRE Wire

void setup() {
  Serial.begin(9600);
  
  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init  
  delay(200);

  u8x8.begin();
  u8x8.setFlipMode(1);
}

float ax, ay, az;

void loop() { 
  
  ax = LIS.getAccelerationX();
  ay = LIS.getAccelerationY();
  az = LIS.getAccelerationZ();
  
  Serial.print("x:"); Serial.print(ax); Serial.print("  ");
  Serial.print("y:"); Serial.print(ay); Serial.print("  ");
  Serial.print("z:"); Serial.println(az);

  u8x8.setFont(u8x8_font_5x7_f  /*u8x8_font_chroma48medium8_r*/);   
  u8x8.setCursor(0, 0);   
  u8x8.print("x:");
  u8x8.print(ax);        
  u8x8.setCursor(0, 1);   
  u8x8.print("y:");
  u8x8.print(ay);        
  u8x8.setCursor(0, 2);   
  u8x8.print("z:");
  u8x8.print(az);        

  delay(1000);
}
