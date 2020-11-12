#include "LedControl.h"

#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 8

LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 1);
    lc.clearDisplay(i);
  }
  Serial.println("ok");
}

int el, col, rw = 0;

void loop() {
  lc.setLed(el, rw, 7-col, true);
  delay(10);
  lc.setLed(el, rw, 7-col, true);
  delay(10);
  col++;
  if (col == 8) {
    col = 0;
    el++;
    if (el == 8) {
      el = 0;
      rw++;
      if (rw == 8) rw = 0;  
    }  
  }
}
