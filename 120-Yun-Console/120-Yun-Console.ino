#include <Console.h>

void setup() {
  Bridge.begin();
  Console.begin();
  while (!Console) {}
  Console.println("Console: ok");  
}

int n = 0;

void loop() {
  Console.println(n);
  delay(1000);
  n++;    
}
