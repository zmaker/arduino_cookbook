void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);  
}

void loop() {
  apri();
  delay(3000);
  chiudi();
  delay(3000);
}

void apri() {
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);  
}

void chiudi() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);  
}
