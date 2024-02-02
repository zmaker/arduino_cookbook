#include <Servo.h>

Servo servo1;
Servo servo2;

int bt, pvbt, max_angle;

void setup() {
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
  servo1.write(0);
  delay(500);
  servo2.write(0);
  delay(500);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);

  //test led:
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);

  //read switch
  do {
    bt = digitalRead(2);
    digitalWrite(3, !digitalRead(3));
    delay(300);
  } while (bt != 1);
  digitalWrite(3, LOW);

  //calibro i servo
  apre();
  delay(500);
  max_angle = 0;
  do {
    servo2.write(max_angle);
    bt = digitalRead(2);
    delay(20);
    max_angle++;
  } while (bt != 0);
  for (int i = max_angle; i >= 0; i--) {
    servo2.write(i);
    delay(10);
  }
  servo2.write(0);
  max_angle = max_angle + 1;
  delay(500);
  chiude();
}

void loop() {
  bt = digitalRead(2);

  if (bt && !pvbt) {
    Serial.println("F1");
    digitalWrite(3, HIGH);
    apre();
    spegne();
    chiude();
  }
  if (!bt && pvbt) {
    Serial.println("F2");
    digitalWrite(3, LOW);
  }

  pvbt = bt;
}

void apre(){
  for (int i = 0; i < 90; i++) {
    servo1.write(i);
    delay(5);
  }
}
void spegne(){
  for (int i = 0; i < max_angle; i++) {
    servo2.write(i);
    delay(5);
  }
  for (int i = max_angle; i >= 0; i--) {
    servo2.write(i);
    delay(5);
  }
}

void chiude(){
  for (int i = 90; i >= 0; i--) {
    servo1.write(i);
    delay(5);
  }
}

