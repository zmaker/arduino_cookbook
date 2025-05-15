void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  int temp = map(v, 0, 1023, 0, 100);
  Serial.println(temp);
  delay(3000);
}
