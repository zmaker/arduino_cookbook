#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High speed I2C

int xship = 64;
int yship = 60;

int xshoot;
int yshoot;
bool FIRING = false;

void setup() {
  u8g2.begin();
  pinMode(6, INPUT);
  randomSeed(analogRead(A1));
  u8g2.setFont(u8g2_font_unifont_t_symbols);    
}

void loop() {
  int v = analogRead(A0);
  xship = map(v, 0,1024, 123,5);
  u8g2.clearBuffer();  

  //sparo
  if (digitalRead(6) && !FIRING) {
    FIRING = true;
    xshoot = xship;
    yshoot = yship-5;  
  }

  //astronave
  u8g2.drawTriangle(xship-5,yship, xship+5,yship, xship,yship-5);

  //missile
  if (FIRING) {
    u8g2.drawLine(xshoot, yshoot, xshoot, yshoot-5);  
    yshoot = yshoot - 3;
    if (yshoot <= 5) {
      FIRING = false;
    }
  }
  
  u8g2.sendBuffer(); 
  delay(50);
}
