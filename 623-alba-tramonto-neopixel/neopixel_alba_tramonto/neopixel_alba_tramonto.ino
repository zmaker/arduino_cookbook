/**
 * . HUE Da 160 (blue) a 6 (giallo)
 * https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors
 */

#include <FastLED.h>

#define NUM_LEDS 16
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS);
}

void loop() {
  
  int h = 0;
  int s = 255;
  //alba
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 160, 200);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  
  for (int i = 0; i < 100; i++) { 
    s = map(i, 0, 100, 255, 0);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  //giorno
  delay(3000);  
  h = 64; //giallo
  s = 0;
  fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
  FastLED.show();
  //tramonto
  
  for (int i = 0; i < 100; i++) { 
    s = map(i, 0, 100, 0, 255);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 64, 0);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 255, 160);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(50);
  }
  //notte
  delay(5000);
  
}
