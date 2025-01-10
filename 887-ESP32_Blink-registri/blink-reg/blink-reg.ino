#include "soc/gpio_struct.h"
#include "driver/gpio.h"

int pin = 4;

void setup() {
  Serial.begin(115200);
  GPIO.enable_w1ts = (1 << pin);
  // 00000001 -> 00010000
  GPIO.out_w1ts = (1 << pin);
  //GPIO.out_w1tc = (1 << pin);
}

void loop() {
  GPIO.out_w1tc = (1 << pin);
  delay(400);
  GPIO.out_w1ts = (1 << pin);
  delay(400);
}
