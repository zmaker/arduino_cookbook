void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(3, digitalRead(2));
}
