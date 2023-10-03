void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);

  cli();
  TCCR2A = _BV(WGM20) | _BV(WGM21) | _BV(COM2B1);
  TCCR2B = _BV(WGM22) | _BV(CS22); //64 -> 977Hz
  OCR2A = 200; //TOP (deve essere >= al valore di OCR2B
  OCR2B = 191; 
  sei();

}

void loop() {
}
