void setup() {
  //Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    dacWrite(25, i);
    //delay(1);
  }

}
