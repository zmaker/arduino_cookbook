
void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0);
  delay(100);
 
  int pwm = map(val, 0,1023, 0,255);
  String str = "val: " + String(val) + " pwm:" + String(pwm);
  Serial.println(str);

  analogWrite(9, pwm);
}
