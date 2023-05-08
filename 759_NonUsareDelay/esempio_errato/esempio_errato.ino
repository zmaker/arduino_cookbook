void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, digitalRead(2));
  
  digitalWrite(3, HIGH);
  delay(500);  
  digitalWrite(3, LOW);
  delay(500);  
}
