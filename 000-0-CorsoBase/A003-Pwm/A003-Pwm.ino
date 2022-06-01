void setup() {
  pinMode(11, OUTPUT);  
}

void loop() {
  int i = 0;

  for (i = 0; i <= 255; i++) {
    //codice da ripetere  
    analogWrite(11, i); 
    delay(10);
  }

  for (i = 255; i >= 0; i--) {
    //codice da ripetere  
    analogWrite(11, i); 
    delay(10);
  }
 
}
