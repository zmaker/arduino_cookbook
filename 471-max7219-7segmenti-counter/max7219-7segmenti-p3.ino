#include "LedControl.h"

const byte CLK = 8;
const byte CS = 9;
const byte DIN = 10;
const byte ELEMENTS = 1;

LedControl lc = LedControl(DIN,CLK,CS,ELEMENTS);

byte digits[10] = {
  B01111110,
  B00110000,
  B01101101,
  B01111001,
  B00110011,
  B01011011,
  B00011111,
  B01110000,
  B01111111,
  B01110011
};

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0, 3);  //luminosità da 0 a 15  
  lc.clearDisplay(0);
  Serial.begin(9600);
}

int el = 0;
int u,d,c,m;

void loop() {
  u++;
  if (u > 9) {
    d++;
    u = 0;
  }
  if (d > 9) {
    c++;
    d = 0;
  }
  if (c > 9) {
    m++;
    c = 0;
  }
  if (m > 9) {
    m = 0;
    c = 0;
    u = 0;  
  }

  
  //lc.clearDisplay(0);
  setDigit(el, 0, u);
  setDigit(el, 1, d);
  setDigit(el, 2, c);
  setDigit(el, 3, m);  
  delay(50);
}

void setDigit(int el, int pos, int n) {
  byte dig = digits[n];
  for (int cl = 0; cl < 8; cl++) {
    if ((dig & (128 >> cl)) >= 1) { 
      //Serial.print("1"); 
      lc.setLed(el, pos, cl, true);
    } else {
      //Serial.print("0"); 
      lc.setLed(el, pos, cl, false);
    }
  }   
}
