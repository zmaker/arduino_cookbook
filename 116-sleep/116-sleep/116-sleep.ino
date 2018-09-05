#include <avr/sleep.h>
#include <avr/power.h>

void pin2Interrupt(void) {
  detachInterrupt(digitalPinToInterrupt(2));
  digitalWrite(13, HIGH);
}

void enterSleep(void) {
  
  attachInterrupt(digitalPinToInterrupt(2), pin2Interrupt, LOW);
  delay(100);
  
  digitalWrite(13, LOW);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sleep_enable();  
  sleep_mode();
  /* Il programma riprende qui. */
    
  sleep_disable(); 
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.println("Setup: ok");

  digitalWrite(13, HIGH);
}

int secondi=0;

void loop() {
  delay(1000);
  secondi++;
  
  Serial.print("Attivo da ");
  Serial.print(secondi, DEC);
  Serial.println(" s.");
  
  if(secondi == 3) {
    Serial.println("Sleep!");
    delay(200);
    secondi = 0;
    enterSleep();
  }
  
}

