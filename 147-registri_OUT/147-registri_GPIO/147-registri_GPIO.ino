//blnk su 13

void setup() {
  //data direction
  DDRB = B00100000; 
}

void loop() {
  PORTB = B00100000;
  delay(500);
  PORTB = B00000000;
  delay(500);
}
