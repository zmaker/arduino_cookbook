void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("EVERY");
}

void loop() {
  if (Serial1.available()) {
    char c = Serial1.read();
    Serial.print(c);
    delay(1);
  }

}
