/*
stepper Y
ENA: 8 
STP: 3
DIR: 6
*/

void setup() {

  pinMode(8, OUTPUT); //ENA
  pinMode(6, OUTPUT); //DIR
  pinMode(3, OUTPUT);

  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
}

void loop() {
  digitalWrite(3, LOW);
  delay(100); 
  digitalWrite(3, HIGH);
  delay(100);
}