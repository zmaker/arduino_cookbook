#include <DistanceSensor.h>

const int echoPin = 4;
const int trigPin = 3;

DistanceSensor sensor(trigPin, echoPin);

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

  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void loop() {
  int dist = sensor.getCM();
  dist = map(dist, 4, 400, 255, 0);
  
  for (int i = 0; i < NUM_LEDS; i++){
    int color = map(i, 0, NUM_LEDS, 0, 255);
    leds[i].setHue(color);
    leds[i] = leds[i].fadeLightBy(random(dist));
  }
  FastLED.show();
  delay(10);
}
