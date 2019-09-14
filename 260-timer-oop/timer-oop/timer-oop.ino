#include "MyTimer.h"

MyTimer t1 = MyTimer();
MyTimer t2 = MyTimer();

void setup() {
  Serial.begin(9600);
  Serial.println("timer ad oggetti");

  t1.set(1000);
  t2.set(1500);
}

void loop() {
  if (t1.check()) {
    Serial.println("t1");
    t1.set(1000);
  }
  if (t2.check()) {
    Serial.println("t2");
    t2.set(1500);
  }
}
