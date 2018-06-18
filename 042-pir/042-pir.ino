void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

void loop() {
  int pir = digitalRead(7);
  Serial.println(pir);
  delay(100);

  if (pir) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
