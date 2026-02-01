void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(3000);

  //impulso
  digitalWrite(1, LOW);
  delay(100);
  digitalWrite(1, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
