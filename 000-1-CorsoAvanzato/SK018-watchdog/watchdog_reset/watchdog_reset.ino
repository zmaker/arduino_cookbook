//https://circuits4you.com/2018/01/24/tutorial-on-arduino-watchdog-timer-setup/

#include <avr/wdt.h>

int stato;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.println("WatchDog Reset"); 
}

void loop() {
  switch(stato){
    case 0:
      if (digitalRead(2)) {
        stato = 1;        
        delay(300);
        wdt_enable(WDTO_4S);         
        Serial.println("\nWdog a 4 secondi... se non premi entro 4s, si resetta"); 
      }
      break;
    case 1:
      if (digitalRead(2)) {
        stato = 0;
        wdt_reset();
        wdt_disable();
        delay(300);
      }   
      delay(100);
      Serial.print(".");      
      break;
    
  }

}
