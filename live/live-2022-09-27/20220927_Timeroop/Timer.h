#ifndef _TIMER_H_
#define _TIMER_H_

#include "arduino.h"

class Timer {
  private:
    unsigned long t1;
    unsigned long durata;
    void (*puntatore_a_funzione)(void);
    int FIRED;
    int LOOP;

  public:
    Timer(unsigned long tm);
    void setAction( void (*pfun)(void) );
    void run();
    void update();
    void isRepeating();

};

#endif