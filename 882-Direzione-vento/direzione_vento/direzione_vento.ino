void setup() {
  Serial.begin(115200);
}

void loop() {
  int d = analogRead(A0);
  Serial.print(d);Serial.print("\t");
  d = map(d, 0, 1024, 0, 360);
  Serial.print("dir: ");Serial.print(d);Serial.println("°");
  delay(300);
}
