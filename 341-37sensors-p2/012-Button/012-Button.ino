/*
  012 - Button
*/

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

int stato = LOW;

void loop() {
  if (digitalRead(2)==LOW) {
    stato = !stato;
    digitalWrite(13, stato);
    delay(300);
  } 
}
