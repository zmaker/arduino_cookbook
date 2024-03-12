void setup() {
  pinMode(3, OUTPUT);  
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(3, i);
    delay(5);
  }
  delay(200);
  for (int i = 255; i >= 0; i--) {
    analogWrite(3, i);
    delay(5);
  }
  delay(200);
}
