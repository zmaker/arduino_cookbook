void setup() {
  pinMode(10, OUTPUT); //e
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT); //e
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  digitalWrite(10, HIGH);
  digitalWrite(5, HIGH);
}

void loop() {
  //avanti
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(1000);

  //stop
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);  
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(1000);

  //indietro
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(1000);

  //stop
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);  
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(1000);

}



