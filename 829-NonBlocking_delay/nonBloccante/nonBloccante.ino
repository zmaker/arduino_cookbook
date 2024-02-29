int bt;
unsigned long t1;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  t1 = millis();
}

void loop() {
  unsigned long dt = millis() - t1;
  if (dt > 1000) {
    digitalWrite(4, !digitalRead(4));
    t1 = millis();
  }

  bt = !digitalRead(2);
  if (bt) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}
