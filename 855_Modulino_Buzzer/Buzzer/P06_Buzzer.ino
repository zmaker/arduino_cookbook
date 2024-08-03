#include <Modulino.h>

ModulinoBuzzer buzzer;

void setup(){
  Modulino.begin();
  buzzer.begin();
}

void loop(){
  buzzer.tone(440, 200);
  delay(200);
  buzzer.tone(0, 500);
  delay(500);

}