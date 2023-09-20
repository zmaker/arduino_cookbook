void setup() {
  Serial.begin(9600);
  
  Serial.print("TCCR2A:\t");Serial.println(TCCR2A, BIN);
  Serial.print("TCCR2B:\t");Serial.println(TCCR2B, BIN);

  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);

  cli(); //disb interrupt
  
  //Uso il timer 2 da 8 bit - lo resetto
  //TCCR2A = 0;                        
  //TCCR2B = 0;
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  //TCCR2B = _BV(CS22);  //64 -> 16000000 / 64 / 256 = 977 Hz
  TCCR2B = _BV(CS21) | _BV(CS20);  //32 -> 16000000 / 32 / 256 = 1953 Hz
  OCR2A = 10;
  //OCR2B = 50;                        

  sei(); //abilita interrupt

  Serial.print("TCCR2A:\t");Serial.println(TCCR2A, BIN);
  Serial.print("TCCR2B:\t");Serial.println(TCCR2B, BIN);

  
}

void loop() {}
