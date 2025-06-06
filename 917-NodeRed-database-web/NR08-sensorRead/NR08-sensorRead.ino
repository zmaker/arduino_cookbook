void setup() {
  Serial.begin(9600);

}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  delay(100);
}
