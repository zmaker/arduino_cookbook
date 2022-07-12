#include "MyLibrary.h"

int attiva(int pin){
  pinMode(pin, OUTPUT);
}
int accendi(int pin){
  digitalWrite(pin, HIGH); 
}
int spegni(int pin){
  digitalWrite(pin, LOW);
}
