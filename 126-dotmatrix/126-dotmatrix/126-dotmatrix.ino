#include "LedControl.h"
#include "caratteri.h"

#define pinCLK 10
#define pinCS 9
#define pinDIN 8

#define ELEMENTS 4

LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS ; i++) {
    lc.shutdown(i,false);  // Wake up displays  
    lc.setIntensity(i,5);  // Set intensity levels
    lc.clearDisplay(i);  // Clear Displays
  }
}

void printCharToElement(char c, int el){
  int charId = (byte)c;
  for (int r = 0; r <= 8; r++){
    lc.setRow(el,r,flipByte(font[charId][r]));    
  }
}

char str[ELEMENTS] = "    ";
String line = String();

void loop() {
  
  if (Serial.available()){
    char p = Serial.read();
    line.concat(p);
    if (p == '\n') {
      line.toCharArray(str, 5);
      Serial.println(str);
      line = String();
    }  
  }

  delay(200);
      
  for (int i = 0; i < ELEMENTS; i++) {
    byte el = ELEMENTS-i-1;  
    printCharToElement(str[i], el);
  }
  
}

