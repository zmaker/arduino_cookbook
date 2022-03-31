void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  if (v == 0) {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else if (v < 300) {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  } else if (v < 600) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
  delay(200);
}
