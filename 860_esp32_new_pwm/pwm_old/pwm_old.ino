void setup() {
  int freq = 1000;
  int res = 8;
  ledcSetup(0, freq, res);

  ledcAttachPin(2, 0);  //pin , canale
}

void loop() {
  for (int i = 0; i < 256; i++) {
    ledcWrite(0, i);
    delay(5);  
  }
  for (int i = 255; i >= 0; i--) {
    ledcWrite(0, i);
    delay(5);  
  }

}