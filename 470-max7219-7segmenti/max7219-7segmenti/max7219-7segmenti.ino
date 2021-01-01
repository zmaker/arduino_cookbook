#include "LedControl.h"

const byte CLK = 8;
const byte CS = 9;
const byte DIN = 10;
const byte ELEMENTS = 1;

LedControl lc = LedControl(DIN,CLK,CS,ELEMENTS);

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0, 3);  //luminosità da 0 a 15  
  lc.clearDisplay(0);
  Serial.begin(9600);
}

/**
 * Display a (hexadecimal) digit on a 7-Segment Display
 * Params:
 *  addr   address of the display
 *  digit  the position of the digit on the display (0..7)
 *  value  the value to be displayed. (0x00..0x0F)
 *  dp     sets the decimal point.   
void setDigit(int addr, int digit, byte value, boolean dp); 
 * 
 */
/*
int c = 9;
void loopko() { 
  lc.clearDisplay(0);
  lc.setChar(0,0,(byte)c,false);
  Serial.println(c);
  delay(200);
  c++;
  if (c >= 10) c = 0;  
}
*/

/**
 *    111
 *   6   2  
 *    777
 *   5   3
 *    444
 *       0
 */

int rw, cl = 0;
void loop() {
  lc.clearDisplay(0);
  for (rw = 0; rw < 8; rw++) {
    for (cl = 0; cl < 8; cl++) {
      Serial.println(cl);
      lc.setLed(0, rw, cl, true);
      delay(1000); 
      lc.setLed(0, rw, cl, false); 
      delay(1000);
    }
  }
  Serial.println("ok");
}
