void setup() {
  pinMode(8, OUTPUT); //ENA
  pinMode(6, OUTPUT); //DIR
  pinMode(3, OUTPUT); //ENA

  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= (1 << COM2B1); //Uscita PWM su OC2B (Pin 3)
  TCCR2A |= (1 << WGM21) | (1 << WGM20); //Fast PWM
  TCCR2B |= (1 << WGM22); //TOP custom

  //prescaler 256
  TCCR2B |= (1 << CS22) | (1 << CS21);

  OCR2A = 624; //TOP - 100Hz
  OCR2B = 312; //DutyCycle 50%

  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
}

unsigned long t1;
int count = 0;

void loop() {
  if ((millis() - t1) > 1000) {
    if (count % 2) {
      OCR2A = 624;
    } else {
      OCR2A = 400;
    }

    count++;
    t1 = millis();
  }

}
