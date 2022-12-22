void setup() {
  Serial.begin(9600);
  

}

void loop() {
  int v = analogRead(A0);
  int vmax = 200;
  Serial.print("v:");
  Serial.print(v);
  Serial.print(",vmax:");
  Serial.print(vmax);
  Serial.print("\n");
  delay(500);
}
