#include <Servo.h>

Servo servo;  

void setup() {
  servo.attach(7);    
}

void loop() {  
  for (int i = 90; i < 180; i++) {
    servo.write(i);
    delay(20);
  }
  servo.write(90);
  delay(1000);
  for (int i = -90; i < 0; i++) {
    servo.write(i);
    delay(20);
  }
  servo.write(90);
  delay(1000);
}

