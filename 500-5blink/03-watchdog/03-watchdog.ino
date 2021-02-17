/*  Blink con watchdog
 *  installa via lib manager:
 *  https://github.com/nadavmatalon/WatchDog
 */

#include "WatchDog.h"

int volatile statoled;

void setup() {
  pinMode(13, OUTPUT);
  WatchDog::init(blinkISR, 1000);
  //WatchDog::setPeriod(OVF_1000MS);
  //WatchDog::stop();
  //WatchDog::start();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void blinkISR() {
  statoled = !statoled;
  digitalWrite(13, statoled);
}
