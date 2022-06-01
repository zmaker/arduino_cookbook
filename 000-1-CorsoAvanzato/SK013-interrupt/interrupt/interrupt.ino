/**
 * Test interrupt (su arduino UNO solo pin 2 e 3)
 * 
 * collegare un tasto al pin 2
 * collegare un led al pin 10
 */

void setup() {
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), cambia, FALLING);
}

volatile int stato = LOW; //volatile può essere cambiata da altre parti di codice

void loop() {
  digitalWrite(10, stato);  
}

void cambia() {
  stato = !stato;  
}
