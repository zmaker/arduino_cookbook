#include "funzioni.h"

void setup() {
  Serial.begin(9600);
  
  int n = test(10);
  Serial.println(n);
}

void loop() {}

