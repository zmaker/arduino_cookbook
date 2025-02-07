volatile unsigned long stepCount = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT); //ENA
  pinMode(6, OUTPUT); //DIR

  // Configurazione del Timer2 per PWM su Pin 3 (OC2B)
  pinMode(3, OUTPUT); // Pin di uscita per PWM

  TCCR2A = 0; // Azzeramento del registro TCCR2A
  TCCR2B = 0; // Azzeramento del registro TCCR2B

  // Configurazione del PWM in modalità Fast PWM (TOP personalizzato)
  TCCR2A |= (1 << COM2B1); // Uscita PWM su OC2B (Pin 3)
  TCCR2A |= (1 << WGM21) | (1 << WGM20); // Modalità Fast PWM
  TCCR2B |= (1 << WGM22); // Modalità Fast PWM con TOP personalizzato
  // 100Hz
  TCCR2B |= (1 << CS22) | (1 << CS21); // Prescaler 256
  OCR2A = 624; // TOP = 624 per 100 Hz
  OCR2B = 312; // Duty cycle 50% (312 è la metà di 624)
  
  // Abilita l'interrupt su OCR2A (Fine di un ciclo PWM)
  TIMSK2 |= (1 << OCIE2A); 

  digitalWrite(8, LOW); //ena
  digitalWrite(6, LOW); //dir
}

ISR(TIMER2_COMPA_vect) {
  stepCount++;  // Conta un passo ogni ciclo PWM completo
  if (stepCount >= 1000) {
    digitalWrite(6, !digitalRead(6)); //dir
    stepCount = 0;
  }
}


void loop() {
  Serial.println(stepCount);  // Stampa il numero di passi fatti
  delay(200); // Stampa ogni secondo
}