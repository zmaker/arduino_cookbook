int stato = LOW;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int bt = digitalRead(2);
  if (bt) {
    stato = !stato;
    digitalWrite(3, stato);
    delay(300);
  }
}
