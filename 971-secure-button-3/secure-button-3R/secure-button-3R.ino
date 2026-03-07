void setup() {
  Serial.begin(9600);

}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);

  if (v > 1000) {
    Serial.println("OPEN");
  } else if (v > 400) {
    Serial.println("PR");
  } else if (v > 170) {
    Serial.println("NP");
  } else {
    Serial.println("CC");
  }

  delay(300);
}
