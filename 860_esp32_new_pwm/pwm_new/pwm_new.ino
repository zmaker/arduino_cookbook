void setup() {
  int freq = 1000;
  int res = 8;
  
  ledcAttach(2, freq, res);

}

void loop() {
  for (int i = 0; i < 256; i++) {
    ledcWrite(2, i);
    delay(5);  
  }
  for (int i = 255; i >= 0; i--) {
    ledcWrite(2, i);
    delay(5);  
  }

}