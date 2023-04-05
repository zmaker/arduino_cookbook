void setup() {
  Serial.begin(115200);
  Serial.println("OPTA BT");
  pinMode(BTN_USER, INPUT);
  pinMode(LED_D0, OUTPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  int bt = !digitalRead(BTN_USER);
  if (bt == HIGH) {
    digitalWrite(D0, HIGH);
    digitalWrite(LED_D0, HIGH);
  } else {
    digitalWrite(D0, LOW);
    digitalWrite(LED_D0, LOW);
  }

}
