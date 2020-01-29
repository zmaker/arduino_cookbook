#include <SimpleDHT.h>
#include "TM1637.h"

#define CLK 2
#define DIO 3

TM1637 tm1637(CLK,DIO);

// for DHT22, 
//      VCC: 5V or 3V
SimpleDHT22 dht22(9);

void setup() {
  Serial.begin(9600);
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

void loop() {
  byte tt = 0;
  byte hh = 0; 
  dht22.read(&tt, &hh, NULL);
  shownumber(tt);
  delay(1000);
  shownumber(hh);
  delay(1000);
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
