/*
https://www.leonardomiliani.com/2013/impariamo-ad-usare-il-watchdog-1/
 */
#include <avr/wdt.h>

void setup() {
  //pulsante collegato tra pin 3 e GND
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  //il Watchdog resta attivo dopo il reset e, se non disabilitato, 
  //esso può provocare il reset perpetuo del microcontrollore
  wdt_disable();
  Serial.println("setup");

  wdt_enable(WDTO_4S);
}

void loop() {
  int bt = HIGH;
  while (bt) {
    bt = digitalRead(2);
    delay(100);
    Serial.print(".");
  }
  Serial.println("exit");
  wdt_reset();
}
