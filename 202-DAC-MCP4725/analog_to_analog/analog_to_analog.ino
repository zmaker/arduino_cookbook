#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (8)

void setup(void) {
  Serial.begin(9600);  
  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  // per le schede cinesi è 0x60
  dac.begin(0x60);  
}

void loop(void) {
  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 4095);
  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
  dac.setVoltage(val, false);  
  Serial.println(val);
  delay(50);
}
