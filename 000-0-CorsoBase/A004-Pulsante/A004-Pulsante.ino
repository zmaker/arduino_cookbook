void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int bt = digitalRead(2);
  Serial.println(bt);
  delay(100);
}
