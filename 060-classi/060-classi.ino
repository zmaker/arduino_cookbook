#include "led.h"

void setup() {
  Serial.begin(9600);
  
  Led led1 = Led();
  Led led2 = Led(2);

  led1.turnOn();
  
  String str = led1.toString();
  Serial.println(str);
  
  led1.turnOff();
  
  str = led1.toString();
  Serial.println(str);
  
}

void loop() {
}




