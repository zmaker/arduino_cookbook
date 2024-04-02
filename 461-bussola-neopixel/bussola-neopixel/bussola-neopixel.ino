/**
 * Bussola a neopixel
 * 
 * GY-273 con QMC5883L
 * 
 libreria
 * https://github.com/mechasolution/Mecha_QMC5883L
 */

#include <FastLED.h>

#define LED_PIN     4
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    24

CRGB leds[NUM_LEDS];


#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 10 );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, 500);
}

int x, y, z, a;
float rad;

void loop() {
  qmc.read(&x, &y, &z);
  
  rad = atan2(y,x); 
  a = rad * (180.0 / PI);
  if (a < 0) {
    a = 360 + a;  
  }
  if (a > 360) {
    a = a - 360;
  }

  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.print(y);
  //Serial.print(" z: ");
  //Serial.print(z);
  Serial.print("\ta: ");
  Serial.print(a);
  Serial.println();
  
  FastLED.clear();
  float n = (((float)a) * 24.0) / 360.0;
  int id = (int)n;
  int nexid = ( (id+1) >= 24 ? 0 : id+1 );
  int nexlev = ((n - (float)id) * 255.0);

  if ((a > 350) || (a < 10)) {
    leds[id].red = (255-nexlev);
    leds[nexid].red = (nexlev);
    Serial.println("n");
  } else {
    leds[id].blue = (255-nexlev);
    leds[nexid].blue = (nexlev);
  }
  
  FastLED.show();
  delay(100);
}
