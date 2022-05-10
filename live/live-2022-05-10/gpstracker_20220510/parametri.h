#ifndef _PARAMETRI_H_
#define _PARAMETRI_H_

//definizione dei pin

#define PIN_GSM_TX 3
#define PIN_GSM_RX 2
#define PIN_GPS_TX 4
#define PIN_GPS_RX 5

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
