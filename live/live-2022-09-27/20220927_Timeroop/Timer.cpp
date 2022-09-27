#include "Timer.h"

Timer::Timer(unsigned long tm){
  durata = tm;
  FIRED = 0;
  LOOP = 0;
}

void Timer::setAction( void (*pfun)(void) ){
  puntatore_a_funzione = pfun;
}

void Timer::run(){
  t1 = millis();
  FIRED = 0;
}

void Timer::update(){
  unsigned long tx = (millis() - t1);
  if ((tx > durata) && !FIRED) {
    puntatore_a_funzione();
    FIRED = 1;
    if (LOOP) {
      FIRED = 0;
      t1 = millis();
    }
  }
}

void Timer::isRepeating(){
  LOOP = 1;
}
