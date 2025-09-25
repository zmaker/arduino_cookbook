#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup() {
  Serial.begin(9600);
  Serial.println("dac");

  if (!dac.begin(0x60)) {
    Serial.println("dac not ready");
    while(true);
  }
}

void loop() {
  for (int i = 0; i < 4096; i++) {
    dac.setVoltage(i, false);
    if ( (i%10) == 0 ) Serial.println(i);
    delay(5);
  }
  delay(2000);
  for (int i = 4095; i >= 0; i--) {
    dac.setVoltage(i, false);
    if ( (i%10) == 0 ) Serial.println(i);
    delay(5);
  }
  delay(2000);
}
