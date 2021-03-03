#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (8)


void setup() {
  Serial.begin(9600);
  dac.begin(0x60);  //l'originale è a 0x62!!
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  dac.setVoltage(map(v, 0,1024, 0,4095), false);
  delay(10);
}
