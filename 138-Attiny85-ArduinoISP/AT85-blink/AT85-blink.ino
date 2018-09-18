void setup() {
  pinMode(0, OUTPUT);  //fisico n.5
}

void loop() {
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  delay(500);
}
