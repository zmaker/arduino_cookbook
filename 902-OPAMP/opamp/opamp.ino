void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  int u = analogRead(A5);
  Serial.print("in: ");
  Serial.print(v);
  Serial.print("\t out:");
  Serial.println(u);
  delay(100);
}
