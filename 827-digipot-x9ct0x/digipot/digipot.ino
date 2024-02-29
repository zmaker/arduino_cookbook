#include <X9C10X.h>

X9C10X pot(5000);

void setup() {
  Serial.begin(9600);

  pot.begin(3,4,2); //pulse, dir, select

  pot.setPosition(99);
  delay(3000);
  pot.setPosition(50);
  delay(3000);
  pot.setPosition(0);
  delay(3000);

  
  
}

void loop() {
  for (int i = 0; i < 100; i++) {
    pot.incr();
    delay(10);
    Serial.print(pot.getOhm());Serial.print(" ohm pos: ");Serial.println(pot.getPosition());
  }
  for (int i = 100; i >= 0; i--) {
    pot.decr();
    delay(10);
    Serial.print(pot.getOhm());Serial.print(" ohm pos: ");Serial.println(pot.getPosition());
  }
}
