void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'a') {
      digitalWrite(13, HIGH);
      Serial.println("ON");
    } else if (ch == 's') {
      digitalWrite(13, LOW);
      Serial.println("OFF");
    }
  }

}
