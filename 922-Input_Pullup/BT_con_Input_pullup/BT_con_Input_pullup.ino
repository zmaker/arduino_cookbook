void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);

}

void loop() {
  int bt = !digitalRead(2);
  Serial.println(bt);
  delay(200);
}
