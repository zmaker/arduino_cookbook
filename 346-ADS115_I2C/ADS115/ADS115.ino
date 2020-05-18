#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1015 adc;

void setup() {
  Serial.begin(9600);
  adc.setGain(GAIN_TWOTHIRDS);

  //adc.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  //adc.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // adc.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // adc.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // adc.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // adc.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  adc.begin();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int val = adc.readADC_SingleEnded(i);  
    Serial.print(i);
    Serial.print(":\t");
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println(" ");
  delay(100);
}
