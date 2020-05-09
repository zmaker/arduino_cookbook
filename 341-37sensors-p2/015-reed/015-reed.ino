/*
  015 - Reed
*/

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2)==LOW) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
}
