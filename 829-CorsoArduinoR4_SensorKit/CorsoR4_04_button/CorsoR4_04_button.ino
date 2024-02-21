void setup() {
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  digitalWrite(3, digitalRead(2));
}
