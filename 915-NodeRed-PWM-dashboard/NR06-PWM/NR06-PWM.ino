void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int val = Serial.parseInt();
    if (val >= 0 && val <= 245) {
      analogWrite(10, val);
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
