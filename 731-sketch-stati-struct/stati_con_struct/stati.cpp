#include "stati.h"
#include <Arduino.h>

void go(struct app_state *st, enum stati dest){
  st->current = dest;
  st->first = true;
}

void app_setup(struct app_state *st){
  if (st->first) {
    Serial.println("setup");
    st->first = false;  
  }  

  st->deviceid = 1234;
  delay(1000);
  go(st, st_park);
}

void app_park(struct app_state *st){
  if (st->first) {
    Serial.println("park");
    st->first = false;  
  }
  Serial.print("devid: ");
  Serial.println(String(st->deviceid));
  
  delay(1000);
  go(st, st_setup);
}
