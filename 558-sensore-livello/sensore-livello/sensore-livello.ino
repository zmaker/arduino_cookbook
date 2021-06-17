/*
sensore livello - XKC-Y25-NPN 
*/

void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  if (!digitalRead(2)) {
    digitalWrite(13, HIGH);  
  } else {
    digitalWrite(13, LOW);  
  }
}
