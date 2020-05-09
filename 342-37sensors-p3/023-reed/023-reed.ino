/*
  023 - reed sensor (attivo)
*/

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
}
