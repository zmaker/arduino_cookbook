#include "parametri.h"
#include "stati.h"

void setup() {
  Serial.begin(9600);

}

void loop() {
  switch (stato) {
    case startup:
      act_startup(&Serial);
      break;
    case work:
      act_work(&Serial);
      break;
    case getposition:
      act_getposition(&Serial);
      break;
    case callservice:
      act_callservice(&Serial);
      break;
  }
}
