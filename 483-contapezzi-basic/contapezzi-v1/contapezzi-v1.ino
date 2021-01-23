/*
 * TM1637.cpp
 */
#include "TM1637.h"
#define CLK 5
#define DIO 4
TM1637 tm1637(CLK,DIO);

int count = 0;

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(2, INPUT);
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop() {  
  if (digitalRead(2) == LOW) {
    count++;   
    delay(300);  
  }  
  if (digitalRead(3)) {
    count = 0;     
  }
  shownumber(count);
}

void shownumber(int n){  
  int d1 = n % 10;
  int d2 = (n/10) % 10;
  int d3 = (n/100) % 10;
  int d4 = (n/1000) % 10;
  tm1637.display(0,d4);
  tm1637.display(1,d3);
  tm1637.display(2,d2);
  tm1637.display(3,d1);
}
