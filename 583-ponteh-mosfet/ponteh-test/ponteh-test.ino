void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  //rotazione 1
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(2000);
  //stop
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(1000);
  //rotazione 2
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(2000);
  //stop
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(1000);
  //fade
  digitalWrite(11, LOW);
  for (int i = 0; i < 256; i++) {  
    analogWrite(10, i);
    delay(10);
  }
  //stop
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(1000);

}
