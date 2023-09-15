void setup() {
  pinMode(8, OUTPUT);
  Serial.begin(9600);

  TCCR1A = 0;
  TCCR1B = 0;

  //TCCR1B |= B00000101;  //1024
  // 16000000 / 1024 = 15 Khz
  //TCCR1B |= B00000100; //256
  // 16000000 / 256 = 62.5 Khz
  TCCR1B |= B00000011; //64
  // 16000000 / 64 = 250 Khz

  TCNT1 = 0x8AB0;

  TIMSK1 |= (1 << TOIE1);
}

void loop() {}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 0x8AB0;
  digitalWrite(8, !digitalRead(8));
}
