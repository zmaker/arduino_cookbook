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

  pinMode(A0, OUTPUT); //led 1
  pinMode(A1, OUTPUT); //led 2
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

int s1, prevs1, s2, prevs2;

void loop() {  
  s1 = !digitalRead(2);
  s2 = !digitalRead(7);
  //ingresso
  if (s1 && !prevs1) {        
    digitalWrite(A0, HIGH);
  }
  if (s1 && prevs1) {        
  }
  if (!s1 && prevs1) {        
    digitalWrite(A0, LOW);
    count++;
  }

  //uscita
  if (s2 && !prevs2) {  
    digitalWrite(A1, HIGH);      
  }
  if (s2 && prevs2) {        
  }
  if (!s2 && prevs2) {
    digitalWrite(A1, LOW);        
    count--;  
    if (count < 0) count = 0;
  }

  if (digitalRead(3)) {
    count = 0;
  }
  
  shownumber(count);

  prevs1 = s1;
  prevs2 = s2;
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
