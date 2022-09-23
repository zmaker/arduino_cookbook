#ifndef _TIMER_H_
#define _TIMER_H_

#include "arduino.h"

class Timer {
  private:
    unsigned long t1;
    unsigned long durata;
    void (*fp)(void);
    int FIRED;
    int LOOP;

  public:
    Timer(unsigned long tm);    
    void isRepeating();
    void run();    
    void loop(); 
    void cback(void (*fun)(void));   
};

#endif
