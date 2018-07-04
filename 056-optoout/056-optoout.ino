int stato = LOW;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, stato);
  delay(500);
  stato = !stato;
}
