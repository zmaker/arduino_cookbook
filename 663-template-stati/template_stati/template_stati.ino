#include "configuration.h"
#include "stati.h"

void setup() {
  Serial.begin(9600);
  Serial.println(_NOME_PRJ_);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  switch(stato) {
    case inizia:
      act_inizia(&Serial);
      break;
    case running:
      act_running(&Serial);
      break;
    case fase1:
      act_fase1(&Serial);
      break;
    case fase2:  
      act_fase2(&Serial);
      break;
  }
}
