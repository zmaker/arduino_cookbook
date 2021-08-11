#include <OneWire.h>
#include "DS2413.h"

OneWire wire(8);
uint8_t address[8] = {0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  wire.reset_search();
  delay(250);
  if (!wire.search(address)) {
    wire.reset_search();
    while(1);  
  }
  write(wire, address, B00000011);
}

void loop() {
  byte n = read(wire, address);
  Serial.println(n, BIN);
  if (bitRead(n, 2) == 0) {
    write(wire, address, B00000010);
  } else {
    write(wire, address, B00000011);
  }
  delay(200);
}
