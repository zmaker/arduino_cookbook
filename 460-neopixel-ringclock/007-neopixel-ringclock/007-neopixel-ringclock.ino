#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

#include <FastLED.h>

#define LED_PIN     4
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    24

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 10 );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, 500);
}

int h = 7;
int m = 15;
int s = 0;
int r,g,b;
int i = 0;
char str[9];

void loop() {
  FastLED.clear();
  //sprintf(str, "%02d:%02d:%02d", h, m, s);
  //Serial.println(str);

  //secondi
  float n = (((float)s) * 24.0) / 60.0;
  int id = (int)n;
  int nexid = ( (id+1) >= 24 ? 0 : id+1 );
  int nexlev = ((n - (float)id) * 255.0);
  //Serial.println(nexlev);

  leds[id].blue = (255-nexlev);
  leds[nexid].blue = (nexlev);

  //minuti
  n = (((float)m) * 24.0) / 60.0;
  id = (int)n;
  nexid = ( (id+1) >= 24 ? 0 : id+1 );
  nexlev = ((n - (float)id) * 255.0);
  //Serial.println(nexlev);

  leds[id].green = 255-nexlev;
  leds[nexid].green = nexlev;

  //ore
  n = (((float)h) * 24.0) / 12.0;
  id = (int)n;
  nexid = ( (id+1) >= 24 ? 0 : id+1 );
  nexlev = ((n - (float)id) * 255.0);
  //Serial.println(nexlev);

  leds[id].red = 255-nexlev;
  leds[nexid].red = nexlev;
  
  
    
  FastLED.show();
  /*
  h++;  //deve anndare da 0 a 12!!!
  if (h >= 12) h = 0;
  i = map(h, 0, 12, 0, 24);
  leds[i].setRGB( 255, 0, 0);

  
*/  
/*

  
*/
  //clock simulato
  s++;
  if (s >= 60) {
    s = 0;   
    m++;
  }  
  if (m >= 60) {
    m = 0;
    h++;   
  }
  if (h >= 12) {
    h = 0;  
  }
  delay(100);
}
