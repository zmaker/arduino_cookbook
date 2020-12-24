#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  pinMode(6, INPUT);
  pinMode(5, OUTPUT);
  randomSeed(analogRead(A1));
  u8g2.setFont(u8g2_font_unifont_t_symbols);    
}

int xship = 64;
int yship = 32;

bool FIRE = false;
int xs, ys;
int ds;
float sa;

void loop() {
  float rot = ((float)map(analogRead(A0), 0,1023, 628,0))/100.0f;

  if (digitalRead(6) && !FIRE) {
    FIRE = true;  
    ds = 10;
    sa = rot;
  }
  
  u8g2.clearBuffer();

  ship(rot);

  //sparo
  if (FIRE) {
    firing();
    ds = ds + 3;  
  }
  
  u8g2.sendBuffer();
  delay(50);
}

void ship(float a) {
   int x = xship + (int)10*cos(a);
   int y = yship + (int)10*sin(a);  
   int xa = xship + (int)5*cos(a + 2.0*PI / 3.0);
   int ya = yship + (int)5*sin(a + 2.0*PI / 3.0);  
   int xb = xship + (int)5*cos(a - 2.0*PI / 3.0);
   int yb = yship + (int)5*sin(a - 2.0*PI / 3.0);  
   u8g2.drawLine(xship, yship, xa, ya);
   u8g2.drawLine(xship, yship, xb, yb);
   u8g2.drawLine(x, y, xa, ya);
   u8g2.drawLine(x, y, xb, yb);
}

void firing() {
   int x = xship + (int)(ds*cos(sa));
   int y = yship + (int)(ds*sin(sa));  
   u8g2.drawPixel(x, y); 
   if ((x > 128) || (x <= 0) || (y<= 0) || (y>64)) {
     FIRE = false; 
   }
}
