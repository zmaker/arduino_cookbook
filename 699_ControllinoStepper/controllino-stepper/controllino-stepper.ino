#include <Controllino.h>

unsigned long ta = 200;

void setup() {
  pinMode(CONTROLLINO_DO4, OUTPUT); //STEP
  pinMode(CONTROLLINO_DO5, OUTPUT); //ENA
  pinMode(CONTROLLINO_DO6, OUTPUT); //DIR

  pinMode(CONTROLLINO_AI12, INPUT); //input 0-10V

  digitalWrite(CONTROLLINO_DO4, HIGH); //STEP
  digitalWrite(CONTROLLINO_DO5, HIGH); //ENA
  digitalWrite(CONTROLLINO_DO6, HIGH); //DIR

  delay(2000);
  digitalWrite(CONTROLLINO_DO5, LOW);

  ta = 1000;
  while (ta > 200) {
    digitalWrite(CONTROLLINO_DO4, !digitalRead(CONTROLLINO_DO4));
    delayMicroseconds(ta);
    ta--;
  }
  ta = 200;
}

void loop() {
  ta = map(analogRead(CONTROLLINO_AI12), 0,1023, 1000, 200);
  if (ta > 500) {
    digitalWrite(CONTROLLINO_DO5, HIGH); //DISABILITO
  } else {
    digitalWrite(CONTROLLINO_DO5, LOW); 
    digitalWrite(CONTROLLINO_DO4, !digitalRead(CONTROLLINO_DO4));
    delayMicroseconds(ta);
  }
}
