void  setup() {
  Serial.begin(115200);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  delay(100);
}