void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(2)) {
    Serial.println(1);
    digitalWrite(13, HIGH);
  } else {
    Serial.println(0);
    digitalWrite(13, LOW);
  }

}
