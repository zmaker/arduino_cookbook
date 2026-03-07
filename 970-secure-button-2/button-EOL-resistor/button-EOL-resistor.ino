void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);

  if (v < 10) {
    Serial.println("NP");
  } else if (v < 400) {
    Serial.println("PR");
  } else {
    Serial.println("KO");
  }

  delay(300);
}
