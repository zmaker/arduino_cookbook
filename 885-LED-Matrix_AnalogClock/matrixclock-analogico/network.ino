#include "config.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

void setupWifi(){
  showMessage("connecting");
  WiFi.begin(ssid, password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    showMessage(String(count));
    count++;
  }
  showMessage("connected");
  delay(500);
}

void setTime(){
  setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
  configTime(0,0, ntpServer);
}