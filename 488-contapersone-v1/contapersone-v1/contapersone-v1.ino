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

  pinMode(3, INPUT); //reset
  pinMode(2, INPUT); //sensore1
  pinMode(7, INPUT); //sensore2
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop() {  
  int s1 = !digitalRead(2);
  int s2 = !digitalRead(7);
  if (s1) {
    count++;  
    delay(300);
  }
  if (s2) {
    count--;  
    if (count < 0) count = 0;
    delay(300);
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
