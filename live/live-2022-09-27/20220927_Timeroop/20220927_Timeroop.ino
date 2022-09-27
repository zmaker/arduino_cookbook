#include "Timer.h"

Timer t1 = Timer(2000);
Timer t2 = Timer(2500);

void evento1();
void evento2();

void setup() {
  Serial.begin(9600);
  Serial.println("Timer OOP");

  t1.setAction(evento1);
  t2.setAction(evento2);
  t2.isRepeating();

  t1.run();
  t2.run();
}

void loop() {
  t1.update();
  t2.update();
}

void evento1() {
  Serial.println("DRINNNN!");
}
void evento2() {
  Serial.println("TIC");
}