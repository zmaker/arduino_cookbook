void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);

  cli();
  TCCR2A = _BV(WGM20) | _BV(COM2A1) | _BV(COM2B1);
  TCCR2B = _BV(CS22); //64 -> 977Hz
  OCR2A = 100;
  //OCR2B = 100;
  sei();

}

void loop() {
  for (uint8_t pwm = 0; pwm < 256; pwm++) {
      OCR2A = pwm;
      delay(10);
  }

}
