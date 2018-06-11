/*
Comanda un relè collegato sul pin 13 tramite un bjt (es 2n2222)
*/

#define ledpin 13

void setup() {
  pinMode(ledpin, OUTPUT);  
}

void loop(){
  digitalWrite(ledpin, HIGH);
  delay(1000);
  digitalWrite(ledpin, LOW);
  delay(1000);
}
