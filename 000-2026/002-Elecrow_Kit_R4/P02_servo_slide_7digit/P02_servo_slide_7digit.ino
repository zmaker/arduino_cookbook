// Demo 2 - Slider (potenziometro lineare) -> servo motore + angolo sul display a 7 segmenti HT16K33
// Kit Elecrow All-in-one Starter Kit per Arduino Nano R4
// Librerie richieste: Servo e HT16K33 (versioni incluse nel repository del kit)

#include <Wire.h>
#include <Servo.h>
#include "HT16K33.h"

#define SLIDER      A0   // nel kit lo slider e' su A0 (lezioni 6 e 19); cambia qui se il tuo e' su un altro pin
#define PIN_SERVO   9

Servo servo;
HT16K33 seg(0x70);       // display a 4 cifre, indirizzo I2C 0x70 (come nella lezione 10)

void setup() {
  servo.attach(PIN_SERVO, 600, 2600);   // impulsi 600-2600 us, come nella lezione 8

  Wire.begin();
  Wire.setClock(100000);
  seg.begin();
  seg.displayOn();
  seg.setBrightness(2);                 // 0..15
  seg.displayClear();
}

void loop() {
  int valore = analogRead(SLIDER);            // 0..1023
  int angolo = map(valore, 0, 1023, 0, 180);  // 0..180 gradi

  servo.write(angolo);
  seg.displayInt(angolo);                     // mostra l'angolo sul display

  delay(50);
}
