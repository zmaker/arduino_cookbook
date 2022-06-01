unsigned long t1, t2;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  t1 = millis();
  t2 = millis();
}

void loop() {
  if ((millis() - t1) > 500) {
      digitalWrite(2, !digitalRead(2));
      t1 = millis();
  }
  if ((millis() - t2) > 300) {
      digitalWrite(3, !digitalRead(3));
      t2 = millis();
  }

}
