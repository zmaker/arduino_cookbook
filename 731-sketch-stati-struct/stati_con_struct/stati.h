#ifndef _STATI_H_
#define _STATI_H_

#include <Arduino.h>

enum stati {st_setup, st_park};

struct app_state {
  enum stati current;  
  bool first = true;
  int deviceid;
  //mettere qui le nuove variabili
};

void go(struct app_state *st, enum stati dest);

void app_setup(struct app_state *st);
void app_park(struct app_state *st);

#endif
