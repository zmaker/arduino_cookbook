//http://alessiobigini.it/2017/03/20/attiny85/
//AT85
//clock internal 8MhZ

//led su pin fisico: #2 

void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  delay(500);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
}
