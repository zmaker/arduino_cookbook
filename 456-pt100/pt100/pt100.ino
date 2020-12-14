void setup() {
  Serial.begin(9600);
}

void loop() {
  float v = analogRead(A0);
  v = map(v, 0, 1023, 0, 5000);

  float pt100 = 1000.0f / ((5000 / v) - 1.0f);
  float temp = map(pt100, 100, 138.4, 0.0, 100.0);
  
  Serial.print("pt100: ");
  Serial.print(pt100);
  Serial.print("\ttemp: ");
  Serial.println(temp);
  delay(300);
}
