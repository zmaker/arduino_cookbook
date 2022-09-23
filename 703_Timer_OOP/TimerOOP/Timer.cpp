#include "Timer.h"
    
Timer::Timer(unsigned long tm){
  durata = tm;
  FIRED = 0;
}

void Timer::isRepeating(){
  LOOP = 1;  
}

void Timer::run(){
  t1 = millis();
  FIRED = 0;
}
void Timer::loop(){
  unsigned long tx = (millis() - t1);
  if ((tx > durata) && !FIRED) {
    Serial.println("OK");  
    fp();
    FIRED = 1;
    if (LOOP) {
      t1 = millis();
      FIRED = 0;
    }
  }
}  

void Timer::cback(void (*fun)(void)){
  fp = fun;
}
