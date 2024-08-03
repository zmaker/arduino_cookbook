#include <Modulino.h>

ModulinoBuzzer buzzer;
ModulinoButtons buttons;

void setup(){
  Modulino.begin();
  buzzer.begin();
  buttons.begin();
}

void loop(){
  if (buttons.update()) {
    if (buttons.isPressed(0)) {
      buzzer.tone(247, 200); //SI
    } else if (buttons.isPressed(1)) {
      buzzer.tone(262, 200); //DO
    } else if (buttons.isPressed(2)) {
      buzzer.tone(392, 200); //SOL
    }
  }

}