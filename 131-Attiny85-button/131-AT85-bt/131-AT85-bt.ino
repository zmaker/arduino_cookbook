//AT85
//clock internal 8MhZ

//led su pin #3      (fisico 2) 
//pulsante su pin #4 (fisico 3)

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
}

void loop() {
  int bt = digitalRead(4);
  if (bt == HIGH) {    
    digitalWrite(3, HIGH);
    delay(1000);    
  }
  digitalWrite(3, LOW);
}
