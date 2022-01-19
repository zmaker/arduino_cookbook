#include <driver/dac.h>
/**
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/dac.html
 * 
 * ESP32 has two 8-bit DAC channels, connected to 
 * GPIO25 (Channel 1) and GPIO26 (Channel 2).
 * 
 */

void setup() {
  dac_output_enable(DAC_CHANNEL_1);
  
}

void loop() {
  for (int i = 0; i < 255; i++) {
    dac_output_voltage(DAC_CHANNEL_1, i);
    delay(1);
  }  
}
