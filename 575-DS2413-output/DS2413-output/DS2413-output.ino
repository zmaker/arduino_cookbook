#include <OneWire.h>
#include "DS2413.h"

OneWire wire(8);
uint8_t address[8] = {0,0,0,0,0,0,0,0};

void setup() {
  wire.reset_search();
  delay(250);
  if (!wire.search(address)) {
    wire.reset_search();
    while(1);  
  }
}

void loop() {
  write(wire, address, B00000000);
  delay(1000);
  write(wire, address, B00000010);
  delay(1000);
  write(wire, address, B00000001);
  delay(1000);
  write(wire, address, B00000011);
  delay(1000);
}
