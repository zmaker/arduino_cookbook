/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 8
LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

#define MAXBARX (ELEMENTS*8)
byte sprite[5] = {
  B00011100,
  B00101010,
  B01111111,
  B00010100,
  B00100010 
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS ; i++) {
    lc.shutdown(i,false);  // Wake up displays  
    lc.setIntensity(i,1);  // 0-15
    lc.clearDisplay(i);  // Clear Displays
  }
  Serial.println("ok");
}

int xs = 0;

void loop() {    
  //pixel(10,1, true); 
  drawSprite(xs,1, sprite);
  delay(100);
  xs++;
  if (xs >= MAXBARX) xs = 0; 
}

void pixel(int x, int y, bool stato){  
  int el = (int)(x / 8);
  int xloc = 7-(x - (8*el));
  y = 7 - y;
  lc.setLed(el,y,xloc, stato);
}

void drawSprite(int xs, int ys, byte data[]){  
  for (int r = 0; r < 5; r++) {
    for (int i = 0; i < 8; i++) {
      bool pix = data[r] & (B10000000 >> i);
      if ((xs+i) <= MAXBARX) { 
        pixel(xs+i, ys+r, pix);
      }
    }
  }
}
