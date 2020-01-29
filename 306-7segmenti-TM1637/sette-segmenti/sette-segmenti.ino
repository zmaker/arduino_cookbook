/*
 * TM1637.cpp
 */
#include "TM1637.h"

#define CLK 2
#define DIO 3

TM1637 tm1637(CLK,DIO);

void setup() {
  Serial.begin(9600);
  tm1637.init();
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.set(BRIGHT_TYPICAL);
  //tm1637.point(POINT_ON);
}

int n = 0;

void loop() {
  shownumber(n);
  n++;
  delay(1000);
}

void shownumber(int n){
  Serial.print(n);
  int d1 = n % 10;
  int d2 = (n/10) % 10;
  int d3 = (n/100) % 10;
  int d4 = (n/1000) % 10;
  Serial.print("\t");
  Serial.print(d4);
  Serial.print("\t");
  Serial.print(d3);
  Serial.print("\t");
  Serial.print(d2);
  Serial.print("\t");
  Serial.println(d1);
  tm1637.display(0,d4);
  tm1637.display(1,d3);
  tm1637.display(2,d2);
  tm1637.display(3,d1);
}
