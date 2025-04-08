void setup() {
  
}

void loop() {
  for (int i = 0; i < 256; i++) {
    analogWrite(6, i);
    delay(20);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(6, i);
    delay(20);
  }

}
