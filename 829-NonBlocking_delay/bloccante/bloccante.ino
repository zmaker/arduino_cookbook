int bt;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);

  bt = !digitalRead(2);
  if (bt) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}
