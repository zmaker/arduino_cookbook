void setup() {
  pinMode(8, OUTPUT);

  TCCR1A = 0;                        
  TCCR1B = 0;      

  TCCR1B |= B00000101;  //15 KhZ

  TCNT1 = 0xFFFF - 8;
  
  TIMSK1 |= (1 << TOIE1);
}

void loop() {}

ISR(TIMER1_OVF_vect) {
    TCNT1 = 0xFFFF - 8;
    digitalWrite(8, !digitalRead(8));
}
