/*
 * https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
 */

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  //imposta prescaler a 1024
  TCCR1A = 0;
  TCCR1B = 0b00000100;

  //reset contatore
  TCNT1 = 0;

  //abilita interrupt
  TIMSK1 = 0b00000001;
}

volatile unsigned int tick = LOW;

ISR(TIMER1_OVF_vect) {
  tick++;  
}

void loop() {
  if (tick%2 == 0) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }  
}
