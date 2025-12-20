#include <Mouse.h>

int stato = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  randomSeed(analogRead(A0));
}

void loop() {
  switch (stato) {
    case 0:
      if (!digitalRead(2)) {
        Serial.println("JUG ON");
        digitalWrite(13, HIGH);
        delay(500);
        //Mouse.begin();        
        stato = 1;
      } 
      break;
    case 1:
      if (!digitalRead(2) == LOW) {
        Serial.println("JUG OFF");
        digitalWrite(13, LOW);
        delay(500);
        stato = 0;
      }
      int x = random(-2, 3);
      int y = random(-2, 3);
      Mouse.move(x, y, 0);
      delay(100 + random(0, 100));
      break;
  }

}
