void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '1') {
      digitalWrite(10, HIGH);
    } else if (cmd == '0') {
      digitalWrite(10, LOW);
    }
  }

}
