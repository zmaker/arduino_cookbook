/*
 https://www.leonardomiliani.com/2013/impariamo-ad-usare-il-watchdog-2/
 */

#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>

volatile unsigned int stato;

void setup() {
  Serial.begin(9600);
  
  MCUSR = 0; //resetta il registro di stato della MCU
  wdt_disable(); //disattiva il watchdog

  wdsetup();
}

void loop() {
  if (stato == HIGH) {
    //è scattato il wd
    stato = LOW;
    wdt_disable();

    Serial.println("scattato wd");  

    wdsetup();     
  }
}

void wdsetup() {
  SREG &= ~(1<<SREG_I); //disattiva tutti gli interrupt
  //imposta il registro del watchdog
  WDTCSR |= ((1<<WDCE) | (1<<WDE));
  //imposta la modalità "interrupt" ed il timeout ad 1 secondo
  WDTCSR = ((1<<WDIE)| (1<<WDP2) | (1<<WDP1)); 
  SREG |= (1<<SREG_I); //riattiviamo gli interrupt globali
}

ISR(WDT_vect) {
   stato = HIGH;
}
  
