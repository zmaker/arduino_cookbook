#include "Timer.h"

Timer t1 = Timer(2000);
Timer t2 = Timer(1000);

void callback1();
void callback2();

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  t1.cback(callback1);
  t2.cback(callback2);
  t2.isRepeating();
  
  t1.run();
  t2.run();
}

void loop() {
  t1.loop();
  t2.loop();
}

void callback1(){
  digitalWrite(3, HIGH);
}
void callback2(){
  digitalWrite(4, !digitalRead(4));
}
