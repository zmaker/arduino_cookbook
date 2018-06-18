void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  delay(100);

  if (v >= 750) {
    digitalWrite(13, HIGH);  
  } else if ((v < 750) && (v > 250)) {
    digitalWrite(13, HIGH);  
    delay(100);
    digitalWrite(13, LOW);
    delay(100);  
  } else if (v <= 250) {
    digitalWrite(13, LOW);
  }

}
