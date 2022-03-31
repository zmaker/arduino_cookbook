#include <Servo.h>

Servo motor;

void setup () {
  motor.attach(6);
}

void loop () {
  int v = analogRead(A0);
  int pos = map(v, 0, 1023, 0, 90);  
  motor.write(pos);
  delay(10);
}
