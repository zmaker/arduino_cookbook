#include <Servo.h>

Servo s;

void setup() {
  s.attach(9);
}

void loop() {
  for (int p = 0; p <= 180; p++) {
    s.write(p);
    delay(5);
  }
  for (int p = 180; p >= 0; p--) {
    s.write(p);
    delay(5);
  }

}
