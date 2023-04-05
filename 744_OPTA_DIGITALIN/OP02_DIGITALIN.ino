void setup() {
  Serial.begin(115200);
  Serial.println("OPTA BT");
  pinMode(A7, INPUT);
  pinMode(LED_D0, OUTPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  int bt = digitalRead(A7);
  if (bt == HIGH) {
    digitalWrite(D0, HIGH);
    digitalWrite(LED_D0, HIGH);
  } else {
    digitalWrite(D0, LOW);
    digitalWrite(LED_D0, LOW);
  }

}
