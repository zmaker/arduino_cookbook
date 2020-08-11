void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);  
  tone(5, 220, 200);
  delay(200);
  digitalWrite(4, LOW);
  delay(200);
  

}
