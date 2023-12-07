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

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

int c = 0;

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    switch((i+c)%3) {
      case 0:
        leds[i] = CRGB::Red;
        break;
      case 1:
        leds[i] = CRGB::White;
        break;
      case 2:
        leds[i] = CRGB::Green;
        break;
    }
    
  }
  FastLED.show();
  delay(1000);
  c++;

  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(10);
    }
    delay(10);
    FastLED.show();
  }

}
