//https://playground.arduino.cc/Learning/ArduinoSleepCode/

#include <avr/sleep.h>
 
int count = 0;                   // counter
  
void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
 
  Serial.begin(9600); 
  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                      // wakeUpNow when pin 2 gets LOW

  Serial.println("sleep...");
  delay(3000);                                    
  sleepNow();
}
 
void sleepNow() {
  digitalWrite(13, LOW);
    /* 
     * The 5 different modes are:
     *     SLEEP_MODE_IDLE         -the least power savings
     *     SLEEP_MODE_ADC
     *     SLEEP_MODE_PWR_SAVE
     *     SLEEP_MODE_STANDBY
     *     SLEEP_MODE_PWR_DOWN     -the most power savings
     */  
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable();
    /* Now it is time to enable an interrupt. We do it here so an
     * accidentally pushed interrupt button doesn't interrupt
     * our running program. if you want to be able to run
     * interrupt code besides the sleep function, place it in
     * setup() for example.
     * 
     * In all but the IDLE sleep modes only LOW can be used.
     * 
     */
 
    attachInterrupt(0,wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                       // wakeUpNow when pin 2 gets LOW
 
    sleep_mode();            // here the device is actually put to sleep!!
                             // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
 
    sleep_disable();         // first thing after waking from sleep:
                             // disable sleep...
    detachInterrupt(0);      // disables interrupt 0 on pin 2 so the
                             // wakeUpNow code will not be executed
                             // during normal running time.
 
}
 
void loop() {
  Serial.print("Awake for ");
  Serial.print(count);
  Serial.println("sec");
  count++;
  delay(1000);                           // waits for a second
 
}

void wakeUpNow() {
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
  digitalWrite(13, HIGH);
}
