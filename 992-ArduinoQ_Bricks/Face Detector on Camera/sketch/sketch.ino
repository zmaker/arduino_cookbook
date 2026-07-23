#include <Arduino_RouterBridge.h>

void setup() {
  Serial.begin(9600);
  Serial.println("arduino ok");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Bridge.begin(9600);
  Bridge.provide("setLed", setLed);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
}

void setLed(int state){
  Serial.println(state);
    if (state == 1) digitalWrite(LED_BUILTIN, LOW);
    else digitalWrite(LED_BUILTIN, HIGH);
}

