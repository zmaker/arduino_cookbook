void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  int v = analogRead(A0);
  v = map(v, 0, 1023, 255, 0);
  v = constrain(v, 10, 100);
  Serial.println(v);
  analogWrite(9, v);
  delay(200);
}
