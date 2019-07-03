
void setup() {
  Serial.begin(9600);
  Serial.println("starting...");
}

void loop() {
  int t = analogRead(A0);
  Serial.println(t);
  delay(100);
}
