void setup() {
  Serial.begin(9600);
}

void loop() {
  //int v = analogRead(A0);
  int v = 20+random(10);
  int u = 80+random(5);
  Serial.print("0,100,");
  Serial.print(u);
  Serial.print(",");
  Serial.println(v);
  delay(100);
}
