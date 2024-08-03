#include "Modulino.h"

ModulinoDistance distance;
ModulinoPixels leds;
ModulinoBuzzer buzzer;

ModulinoColor OFF(0, 0, 0);

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  distance.begin();
  leds.begin();
  buzzer.begin();
}

unsigned long t1;
int pausa = 3000;
int distanza = 0;

void loop() {
  if (distance.available()) {
    distanza = distance.get();
    Serial.println(distanza);
    int lev = map(distanza, 0, 400, 0, 7);
    lev = constrain(lev, 0, 7);
    for (int i = 0; i < 8; i++) {
      if (i < lev) leds.set(i, BLUE, 10);
      else leds.set(i, OFF, 10);      
    }
    leds.show();
  } else distanza = 0;

  pausa = map(distanza, 0, 400, 10, 1000);

  if ((millis() - t1) > pausa){
    if (distanza > 0) {
      buzzer.tone(440, 100);
    } else {
      buzzer.tone(0, 10);
    }
    
    t1 = millis();
  }

  delay(10);
}