void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(3000);
  //digitalWrite(13, LOW);
  for (int i = 0; i < 5; i++) {
    digitalWrite(12, HIGH);
    delay(200);
    digitalWrite(12, LOW);
    delay(200);
  } 
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  delay(3000);
  digitalWrite(11, LOW);
}
