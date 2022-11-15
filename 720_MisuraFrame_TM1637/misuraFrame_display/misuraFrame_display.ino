#include "TM1637.h"

#define PIN_CLK 3
#define PIN_DIO 4
TM1637 tm1637(PIN_CLK, PIN_DIO);

unsigned long t1;

volatile int count = 0;

void setup() {
  Serial.begin(9600);

  tm1637.init();
  tm1637.set(3); //da 0 a 7

  attachInterrupt(digitalPinToInterrupt(2), conta, FALLING);
}

void loop() {
  if ((millis() - t1) >= 1000) {
    shownumber(count/2);
    count = 0;
    t1 = millis(); 
  }
}

void shownumber(int n){
  int d1 = n%10;
  int d2 = (n/10)%10;
  int d3 = (n/100)%10;
  int d4 = (n/1000)%10;
  tm1637.display(0, d4);
  tm1637.display(1, d3);
  tm1637.display(2, d2);
  tm1637.display(3, d1);
}

void conta(){
  count++;  
}
