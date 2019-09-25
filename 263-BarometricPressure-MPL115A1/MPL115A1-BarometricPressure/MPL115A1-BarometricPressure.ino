#include <SPI.h>
#include "MPL115A1.h"

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(MPL115A1_SELECT_PIN, OUTPUT);
  pinMode(MPL115A1_ENABLE_PIN, OUTPUT);

  digitalWrite(MPL115A1_SELECT_PIN, HIGH);
}

float pressure_pKa = 0;
float temperature_c= 0;
long altitude_ft = 0;

/* Barometric pressue in weather forcasts is adjusted to sea level.
   Add 1200 Pa for each 100m above sea level in elevation.  
   Multiply by 0.000295333727 to convert to inches of Hg 
   For my location (80m), that comes to 0.2832 */ 
double seaLevelAdjInHg = 0.000295333727 * 1200 * (80 / 100);
double seaLevelAdjmmHg = 0.000295333727 * 1200 * (80 / 100) * 25.4;

void loop() {
  pressure_pKa = calculatePressurekPa();
  temperature_c = calculateTemperatureC();
  //double pressure = KPA_TO_INHG(pressure_pKa); 
  double pressure = KPA_TO_MMHG(pressure_pKa); 
  //pressure += seaLevelAdjInHg;
  pressure += seaLevelAdjmmHg;

  Serial.print(pressure, 2);
  Serial.println(" mmHg");

  delay(5000);
  
}
