/* arduino leonardo as keyboard */
#include "Keyboard.h"

#define BUTTON 7

void setup() {
  pinMode(BUTTON, INPUT);  
  Keyboard.begin();
}

int c = 0;

void loop() {
  if (digitalRead(BUTTON)) {
    Keyboard.println("Hello World!");
    Keyboard.println(c);
    Keyboard.println("\n\r");
    c++;
    delay(2000);
  }    
}
