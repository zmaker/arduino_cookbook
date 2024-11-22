void setup() {
  Serial.begin(115200);
}

void loop() {
  int v = analogRead(A0);
  Serial.print(v);Serial.print("\t");
  v = map(v, 0, 1024, 0, 3000);
  float vel = (float)v / 100.0;
  Serial.print("vel: ");Serial.print(vel);Serial.println(" m/s");
  delay(500);
}
