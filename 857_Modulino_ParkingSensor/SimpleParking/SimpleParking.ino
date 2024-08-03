#include "Modulino.h"

ModulinoDistance distance;
ModulinoPixels leds;

ModulinoColor OFF(0, 0, 0);

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  distance.begin();
  leds.begin();
  
}

void loop() {
  if (distance.available()) {
    int measure = distance.get();
    Serial.println(measure);
    int lev = map(measure, 0, 400, 0, 7);
    lev = constrain(lev, 0, 7);
    for (int i = 0; i < 8; i++) {
      if (i < lev) leds.set(i, BLUE, 10);
      else leds.set(i, OFF, 10);      
    }
    leds.show();
  }
  delay(10);
}