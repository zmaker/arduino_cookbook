#include <Modulino.h>

ModulinoKnob knob;

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  knob.begin();
}

void loop(){
  int position = knob.get();
  bool click = knob.isPressed();

  Serial.println(position);

  if (click){
    Serial.println("Clicked!");
    position = 0;
  }

}
