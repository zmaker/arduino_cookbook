/**
 * https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier?view=all
 */
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  Serial.begin(9600);
  thermo.begin(MAX31865_2WIRE);  // set to 3WIRE or 4WIRE as necessary
}

void loop() {
  float temp = thermo.temperature(RNOMINAL, RREF);
  Serial.println("temp: ");
  Serial.println(temp);
  delay(1000);
}
