void setup() {
  pinMode(4, OUTPUT); 
  pinMode(6, INPUT); 
}

void loop() {
  if (digitalRead(6)) {
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
  }
}
