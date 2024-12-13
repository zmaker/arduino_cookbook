#include "config.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

void setup() {
  setupDisplay();
  setupWifi();
  setTime();
}

unsigned long t1;
unsigned long t2;

void loop() {
  if ((millis() - t1) > 300){
    if (getLocalTime(&timeinfo)) {
      dma_display->clearScreen();
      clock(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }
    t1 = millis();
  }

  if ((millis() - t2) > 3600000){
    setTime();
    t2 = millis();
  }
}
