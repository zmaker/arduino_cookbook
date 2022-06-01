#include <Servo.h>

Servo motor;

void setup () {
  motor.attach(6);
}

void loop () {
  for (int i = 0; i < 90; i++) {
    motor.write(i);
    delay(10);
  }
  for (int i = 90; i >= 0; i--) {
    motor.write(i);
    delay(10);
  }
}
