/*
stepper Y
ENA: 8 
STP: 3
DIR: 6
*/

void setup() {

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
  
  //200Hz
  /*TCCR2B |= (1 << CS22); // Prescaler 64
  OCR2A = 124; // TOP = 124 per 200 Hz
  OCR2B = 62;  // Duty cycle 50% (62 è la metà di 124)
  */

  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
}

void loop() {

}