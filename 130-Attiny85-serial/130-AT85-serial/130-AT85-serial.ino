//http://alessiobigini.it/2017/03/20/attiny85/
//AT85
//clock internal 8MhZ

#include <SoftwareSerial.h>

#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3

SoftwareSerial SSerial(RX, TX);

void setup() {
  SSerial.begin(9600);
}

int i = 0;

void loop() {
  SSerial.println(i);
  delay(1000);  
  i++;
}
