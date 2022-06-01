void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);  
}

void loop() {  
  if ( digitalRead(2) ) {
    //codice da eseguire se la expr è vera
    digitalWrite(13, HIGH);
  } else {
    //codice da eseguire se la expr è false
    digitalWrite(13, LOW);
  }
}
