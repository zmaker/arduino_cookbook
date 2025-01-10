/*
Per leggere un pin a cui è collegato un pulsante con una resistenza 
pull-down esterna
*/

#include "soc/gpio_struct.h"
#include "driver/gpio.h"

int pin = 5;

void setup() {
  Serial.begin(115200);
  GPIO.enable_w1tc = (1 << pin);
  GPIO.pin[pin].pad_driver = 0; // 1 open drain
  GPIO.func_in_sel_cfg[pin].sig_in_sel = 0;
}

void loop() {
  int stato = GPIO.in & (1 << pin);
  Serial.println(stato);
  if (stato) {
    Serial.println("premuto");
  } 
  delay(200);
}
