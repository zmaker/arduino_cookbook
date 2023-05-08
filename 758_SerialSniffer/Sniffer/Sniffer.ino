void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  if (Serial1.available()) {
    char c = Serial1.read();  
    Serial2.write(c);
    Serial.print("\n>");
    Serial.write(c);
  }

  if (Serial2.available()) {
    char c = Serial2.read();  
    Serial1.write(c);
    Serial.print("\n<");
    Serial.write(c);
  }

}
