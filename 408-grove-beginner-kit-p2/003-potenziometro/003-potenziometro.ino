void setup() {
  pinMode(4, OUTPUT); 
}

void loop() {
  int pausa = analogRead(A0); 
  pausa = map(pausa, 0, 1024, 10, 1000);
  digitalWrite(4, HIGH);
  delay(pausa);
  digitalWrite(4, LOW);
  delay(pausa);
}
