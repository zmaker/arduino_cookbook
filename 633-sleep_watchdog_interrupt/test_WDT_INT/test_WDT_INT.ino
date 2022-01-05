/*
 * Sketch for testing sleep mode with wake up on WDT.
 * http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
 * 
 * http://donalmorrissey.blogspot.com/2010/04/putting-arduino-diecimila-to-sleep.html
 * 
 * Usa un led su pin 13 e pulsante con input_pullup su pin 2
 */
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

volatile int f_wdt=1;

/***************************************************
 *  Name:        ISR(WDT_vect)
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 ***************************************************/
ISR (WDT_vect) {
  if (f_wdt == 0) {
    f_wdt=1;
  } 
}

/***************************************************
 *  Name:        pin2Interrupt
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Service routine for pin2 interrupt  
 ***************************************************/
void pin2Interrupt() {
  /* This will bring us back from sleep. */
  
  /* We detach the interrupt to stop it from 
   * continuously firing while the interrupt pin
   * is low.
   */
  detachInterrupt(0);

  //per il risveglio riattivo il flag wdt
  if (f_wdt == 0) {
    f_wdt=1;
  }
}

/***************************************************
 *  Name:        enterSleep
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Enters the arduino into sleep mode.
 ***************************************************/
void enterSleep() {
  /* Setup pin2 as an interrupt and attach handler. */
  //https://manned.org/SLEEP_MODE_PWR_SAVE
  attachInterrupt(0, pin2Interrupt, FALLING);
  
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
}

/***************************************************
 *  Name:        setup
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Setup for the serial comms and the
 *                Watch dog timeout. 
 ***************************************************/
void setup() {
  Serial.begin(9600);
  Serial.println("WDT & INT");
  
  delay(100); //Allow for serial print to complete.

  pinMode(13,OUTPUT);
  pinMode(2, INPUT_PULLUP);

  /*** Setup the WDT ***/
  //WDP3 - WDP2 - WPD1 - WDP0 - time
  // 0      0      0      0      16 ms
  // 0      0      0      1      32 ms
  // 0      0      1      0      64 ms
  // 0      0      1      1      0.125 s
  // 0      1      0      0      0.25 s
  // 0      1      0      1      0.5 s
  // 0      1      1      0      1.0 s
  // 0      1      1      1      2.0 s
  // 1      0      0      0      4.0 s
  // 1      0      0      1      8.0 s
  
  /* Clear the reset flag. */
  //MCUSR &= ~(1<<WDRF);
  wdt_reset();
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

/* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; // 8.0 seconds
  //WDTCSR = 1<<WDP2 | 1<<WDP1; // 1.0 seconds
  //WDTCSR = 1<<WDP3; // 4.0 seconds
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
  Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete.
  //attachInterrupt(0, pin2Interrupt, FALLING);
}



/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
void loop() {
  if(f_wdt == 1) {
    /* Toggle the LED */
    digitalWrite(13, !digitalRead(13));
    
    /* Don't forget to clear the flag. */
    f_wdt = 0;
    
    /* Re-enter sleep mode. */
    enterSleep();
  } else {
    /* Do nothing. */
  }
}
