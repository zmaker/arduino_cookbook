//RTCLib by Adafruit x DS1307
#include "RTClib.h"
RTC_DS1307 rtc;

#include <Wire.h>
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

  //impostazione modulo RTC DS1307 (I2C)
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   
  }
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
  
  //clock simulato
  DateTime now = rtc.now();
  h = now.hour();
  m = now.minute();
  s = now.second();  
  //riporto le ore tra 0 e 12.
  if (h >= 12) {
    h = h - 12;  
  }
  delay(100);
}
