#include "stati.h"

app_state stato;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  switch (stato.current) {
    case st_setup:
      app_setup(&stato);
      break;
    case st_park:
      app_park(&stato);
      break;      
  }
}
