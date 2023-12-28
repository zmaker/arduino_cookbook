void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  delay(3000);
  //analogReference(DEFAULT);
}

void loop() {
  int n = analogRead(A0);
  int v = map(n, 0, 1023, 0, 3200);
  Serial.print(n);Serial.print(" mV: ");Serial.println(v);
  delay(300);
}
