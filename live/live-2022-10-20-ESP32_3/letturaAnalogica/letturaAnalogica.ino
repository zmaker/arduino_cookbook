void setup() {
  Serial.begin(115200);
  analogReadResolution(12); //da 9 a 12
}

void loop() {
  int v = analogRead(4);
  Serial.println(v);
  delay(250);
}
