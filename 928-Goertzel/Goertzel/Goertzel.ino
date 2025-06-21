#include <Goertzel.h>

Goertzel TONE(440.0);
int buff[100];

float offset;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);

  for (int i = 0; i < 10; i++) {
    offset += analogRead(A0);
    delay(10);
  }
  offset = offset / 10.0;

}

void loop() {
  for (int i = 0; i < 100; i++) {
    buff[i] = analogRead(A0) - offset;
  }

  float f1 = TONE.Mag(buff, 100);

  digitalWrite(2, LOW);
  if (f1 > 2000) {
    digitalWrite(2, HIGH);
  }

  Serial.print("0, 5000, ");Serial.print(f1);Serial.println("");
}
