/*
  017 - HAL Sensor (analogico) - 49E
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //pinMode(2, INPUT);
}

void loop() {
  int v = analogRead(A0);
  int pwm = map(v, 550, 150, 0, 255);
  analogWrite(6, pwm);
  Serial.println(v);
  delay(10);
  /*
  if (digitalRead(2)==LOW) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
  */
}
