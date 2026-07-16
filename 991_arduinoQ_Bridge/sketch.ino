//installa la libreria!!!!!!!!!!!
#include "Arduino_RouterBridge.h"

int i = 0;

void myfun(int c) {    
  Serial.println(c);
  digitalWrite(LED_BUILTIN, c%2);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  Bridge.begin(9600);
  Bridge.provide("myfun", myfun);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  i++;
  Bridge.call("fromQRB", i);
  delay(1000);
  
}


