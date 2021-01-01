/**
 * LED - pin 10,11,12,13 
 * Sono collegati verso i 5V!!!!
 */
 
void setup() {
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(10+i, HIGH);  
    delay(200);
  }
  for (int i = 4; i >= 0; i--) {
    digitalWrite(10+i, LOW);  
    delay(200);
  }
}
