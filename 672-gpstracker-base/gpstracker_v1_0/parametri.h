#ifndef _PARAMETRI_H_
#define _PARAMETRI_H_

#define TIMEOUT_SENSORE 5000

enum stati {startup, work, getposition, callservice} stato = startup;
bool FIRST = true;

unsigned long t1;

struct gps_location {
  float lat;
  float lon;
  float alt;
} position;

#endif
