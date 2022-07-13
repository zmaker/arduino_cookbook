#ifndef _GAUGE_H_
#define _GAUGE_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Gauge {
  
  private:
    int xc;
    int yc;
    float raggio;
    
    Adafruit_SSD1306 *display;

  public:    
    Gauge(int x, int y, int r);
    void setValue(int p);
    void setDisplay(Adafruit_SSD1306 *display);
};

#endif
