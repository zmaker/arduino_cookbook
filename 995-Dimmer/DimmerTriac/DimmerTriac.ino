// https://github.com/fabianoriccardi/dimmable-light
#include <dimmable_light.h> //con IDE 1.8.3

const int syncPin = 2;
const int outPin = 9;

DimmableLight dimmer(outPin);

void setup() {
  Serial.begin(115200);
  DimmableLight::setSyncPin(syncPin);
  DimmableLight::begin();
}

void loop() {
  for (int i = 0; i < 256; i++) {
    dimmer.setBrightness(i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    dimmer.setBrightness(i);
    delay(10);
  }

}