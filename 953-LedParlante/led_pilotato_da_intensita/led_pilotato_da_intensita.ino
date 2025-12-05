void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  int v = analogRead(A0);
  v = map(v, 0, 1023, 0, 255);
  Serial.print("0,255,");Serial.println(v);
  analogWrite(3, v);
  delay(50);
}
