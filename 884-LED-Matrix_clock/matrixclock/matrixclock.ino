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
  if ((millis() - t1) > 500){
    if (getLocalTime(&timeinfo)) {
      sprintf(strt, "%02d:%02d:%02d:", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
      sprintf(strh, "%02d/%02d/%04d:", timeinfo.tm_mday, timeinfo.tm_mon+1, timeinfo.tm_year+1900);
      dma_display->clearScreen();
      dma_display->setTextSize(1);
      dma_display->setTextWrap(false); 
      dma_display->setTextColor(myWHITE);
      dma_display->setCursor(9, 4);  
      dma_display->println(strt);
      dma_display->setCursor(3, 20);  
      dma_display->println(strh);
    }
    t1 = millis();
  }

  if ((millis() - t2) > 3600000){
    setTime();
    t2 = millis();
  }
}
