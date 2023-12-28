#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN            6
#define NUM_LEDS            150
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);

  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
  FastLED.show();
}

int c = 0;

void loop() {
  if ((c%5) == 0) leds[0] = CRGB::Red;
  if ((c%5) == 1) leds[0] = CRGB::White;
  if ((c%5) == 2) leds[0] = CRGB::Blue;
  if ((c%5) == 3) leds[0] = CRGB::Black;
  if ((c%5) == 4) leds[0] = CRGB::Black;
  c++;
  
  for (int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i] = leds[i-1];
  }
  FastLED.show();
  delay(100);
}
