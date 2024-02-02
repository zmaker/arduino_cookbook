#include <Servo.h>

Servo servo1, servo2;

#define MAX_APERTURA 165

int bt, pvbt;

void setup() {
  Serial.begin(9600);
  servo1.attach(5);
  servo1.write(0);
  servo2.attach(6);
  servo2.write(0);

  delay(1000);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
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

void apre() {
  for (int i = 0; i < 90; i++) {
    servo1.write(i);
    delay(5);
  }
}

void spegne() {
  for (int i = 0; i < MAX_APERTURA; i++) {
    servo2.write(i);
    delay(5);
  }
  for (int i = MAX_APERTURA; i >= 0; i--) {
    servo2.write(i);
    delay(5);
  }
}

void chiude() {
  for (int i = 90; i >= 0; i--) {
    servo1.write(i);
    delay(5);
  }
}
