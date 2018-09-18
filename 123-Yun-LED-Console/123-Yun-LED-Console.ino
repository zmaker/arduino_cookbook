#include <Console.h>

void setup() {
  Bridge.begin();
  Console.begin();
  while (!Console) {}
  Console.println("Console: ok");  

  pinMode(13, OUTPUT);
}

void loop() {
  if (Console.available()) {
    char c = Console.read();
    if (c == 'a') {
      digitalWrite(13, HIGH);  
    }
    if (c == 's') {
      digitalWrite(13, LOW);  
    }
  }
  
}
