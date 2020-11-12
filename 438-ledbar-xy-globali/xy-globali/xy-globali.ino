#include "LedControl.h"
#define pinCLK 4
#define pinCS 3
#define pinDIN 2
#define ELEMENTS 8

LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS; i++) {
    lc.shutdown(i,false);  // Wake up displays  
    lc.setIntensity(i,1);
    lc.clearDisplay(i); 
  }
}
void loop() {
  pixel(10, 1, true);
}

void pixel(int x, int y, bool stato){
  int el = (int)(x/8);
  int xloc = 7 - (x - (8*el));
  y = 7 - y;
  lc.setLed(el, y, xloc, stato);
}
