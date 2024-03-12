void setup() {
  Serial.begin(9600);
}

void loop() {
  //lettura analogica da 0 a 1023
  int pot = analogRead(A0);
  //stampo il valore analogico
  Serial.println(pot);

  int pwm = map(pot, 0, 1023, 0, 255);

  analogWrite(3, pwm);

  delay(100);
}
