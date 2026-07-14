void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "ON") {
      digitalWrite(13, HIGH);
      Serial.println("ON");
    } else if (cmd == "OFF") {
      digitalWrite(13, LOW);
      Serial.println("OFF");
    }
  }

}
