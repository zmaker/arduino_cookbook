int t = 0;

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, !digitalRead(2));
  delay(10 + t%50);
  t++;
}
