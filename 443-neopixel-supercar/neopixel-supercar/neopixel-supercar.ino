#include <FastLED.h>

#define NUM_LEDS 24
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, 2, GRB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

void loop() {
  for (int i = 0; i < NUM_LEDS+3; i++) {
    if (i < NUM_LEDS) leds[i] = CRGB(255,0,0);
    if ((i > 0) && (i < NUM_LEDS+1)) leds[i-1] = CRGB(100,0,0);
    if ((i > 1) && (i < NUM_LEDS+2)) leds[i-2] = CRGB(10,0,0);
    if ((i > 2) && (i < NUM_LEDS+3)) leds[i-3] = CRGB(0,0,0);
    FastLED.show();
    delay(50);
  }

  for (int i = NUM_LEDS-1; i >= -3; i--) {
    if (i >= 0) leds[i] = CRGB(255,0,0);
    if ((i >= -1) && (i < NUM_LEDS-1)) leds[i-1] = CRGB(100,0,0);
    if ((i >= -2) && (i < NUM_LEDS-2)) leds[i-2] = CRGB(10,0,0);
    if ((i >= -3) && (i < NUM_LEDS-3)) leds[i-3] = CRGB(0,0,0);
    FastLED.show();
    delay(50);
  }

}
