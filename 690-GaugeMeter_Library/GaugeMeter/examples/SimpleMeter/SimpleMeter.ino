#include "Gauge.h"

//https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define RAGGIO 10
int xc = 30;
int yc = 30;
Gauge meter(xc, yc, RAGGIO);

unsigned long t1;

void setup() { 
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font  
  display.clearDisplay();
  
  meter.setDisplay(&display);
}

void loop() {
  if ((millis() - t1) > 100) {
    int v = analogRead(A0);
    int perc = map(v, 0, 1023, 0, 100);
    
    meter.setValue(perc);
    
    t1 = millis();
  }
}
