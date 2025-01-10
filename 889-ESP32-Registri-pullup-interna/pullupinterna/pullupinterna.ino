#include "soc/gpio_struct.h"
#include "driver/gpio.h"

int pin = 5;

void setup() {
  Serial.begin(115200);
  
  gpio_config_t io_conf = {};
  io_conf.pin_bit_mask = (1 << pin);
  io_conf.mode = GPIO_MODE_INPUT;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpio_config(&io_conf);
}

void loop() {
  int stato = (GPIO.in & (1 << pin)) ? HIGH : LOW;
  Serial.println(stato);
  if (!stato) {
    Serial.println("premuto");

  }
  delay(200);

}
