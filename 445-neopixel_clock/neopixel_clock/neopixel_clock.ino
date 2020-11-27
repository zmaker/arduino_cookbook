#include <FastLED.h>

//RTCLib by Adafruit x DS1307
#include "RTClib.h"
RTC_DS1307 rtc;

CRGB hled[24];
CRGB mled[16];
CRGB sled[8];

void setup() {
  Serial.begin(9600);
  
  clearleds();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {
  DateTime now = rtc.now();
  showHour(now.hour());
  showMinute(now.minute());
  showSecond(now.second());
  FastLED.show();
  delay(500);
  //Serial.println(now.second());
}

void clearleds() {
  FastLED.addLeds<WS2812, 2, GRB>(sled, 8);
  for (int i = 0; i < 8; i++) {
    sled[i] = CRGB(0,0,0);
  }  
  FastLED.addLeds<WS2812, 4, GRB>(mled, 16);
  for (int i = 0; i < 16; i++) {
    mled[i] = CRGB(0,0,0);
  }  
  FastLED.addLeds<WS2812, 3, GRB>(hled, 24);
  for (int i = 0; i < 24; i++) {
    hled[i] = CRGB(0,0,0);
  } 
  FastLED.show();
}

void showHour(int h){
  int n = map(h, 0, 60, 0, 24);
  int r,g,b = 0;
  pickcolor(n, &r, &g, &b);  
  hled[n] = CRGB(r,g,b);
  if (n > 0) hled[n-1] = CRGB(0,0,0);   
  else hled[23] = CRGB(0,0,0);  
}

void showMinute(int m) {
  int n = map(m, 0, 60, 0, 16);
  int r,g,b = 0;
  pickcolor(n, &r, &g, &b);  
  mled[n] = CRGB(r,g,b); 
  if (n > 0) mled[n-1] = CRGB(0,0,0);   
  else mled[15] = CRGB(0,0,0);  
}

void showSecond(int s) {
  int n = map(s, 0, 60, 0, 8);
  int r,g,b = 0;
  pickcolor(n, &r, &g, &b);  
  sled[n] = CRGB(r,g,b);
  if (n > 0) sled[n-1] = CRGB(0,0,0);   
  else sled[7] = CRGB(0,0,0);  
}

void pickcolor(int n, int *r, int *g, int *b){
  switch(n%5){
    case 0:
    *r = 255;
    break;
    case 1:
    *b = 255;
    break;
    case 2:
    *b = 255;
    break;
    case 3:
    *r = 127;
    *g = 127;
    break;
    case 4:
    *g = 127;
    *b = 127;
    break;    
  }  
}
