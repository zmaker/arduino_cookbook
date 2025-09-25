/**************************************************************************/
/*! 
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a triangle wave with the MCP4725 DAC.   

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935
 
    Adafruit invests time and resources providing this open source code, 
    please support Adafruit and open-source hardware by purchasing 
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
bool CONF;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  CONF = dac.begin(0x60);
    
  if (CONF) {
    Serial.println("Generating a triangle wave");
  } else {
    Serial.println("Not configured");
    while(true);
  }
}

void loop(void) {
    for (int i = 0; i < 4095; i++) {
      dac.setVoltage(i, false);
      if ((i%10) == 0) Serial.println(i);
      delay(5);
    }
    delay(2000);
    for (int i = 4095; i > 0; i--) {
      dac.setVoltage(i, false);
      if ((i%10) == 0) Serial.println(i);
      delay(5);
    }
    delay(2000);
}