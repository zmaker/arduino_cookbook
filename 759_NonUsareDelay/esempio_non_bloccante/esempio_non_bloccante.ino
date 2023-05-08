unsigned long postit1;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  postit1 = millis();
}

void loop() {
  digitalWrite(4, digitalRead(2));
 
  if ( (millis() - postit1) >= 500) {
    digitalWrite(3, !digitalRead(3));  
    postit1 = millis();
  }
}
