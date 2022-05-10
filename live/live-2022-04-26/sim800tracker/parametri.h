#ifndef PARAMETRI_H
#define PARAMETRI_H

enum stati {startup, work, getposition, callservice} stato = startup;
bool FIRST = true;

#define PIN_GSM_TX 2
#define PIN_GSM_RX 3
#define PIN_GPS_TX 4
#define PIN_GPS_RX 5

#endif
