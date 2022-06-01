void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);

  if (digitalRead(3)) {
    digitalWrite(4, HIGH);  
  } else {
    digitalWrite(4, LOW);  
  }
}
