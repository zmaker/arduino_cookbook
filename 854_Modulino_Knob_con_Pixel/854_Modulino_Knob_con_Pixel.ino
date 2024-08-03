#include <Modulino.h>

ModulinoKnob knob;
ModulinoPixels leds;

ModulinoColor OFF(0, 0, 0);

int pos, oldpos;

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  knob.begin();
  leds.begin();
}

void loop(){
  pos = knob.get();
  bool click = knob.isPressed();

  Serial.println(pos);

  if (click){
    Serial.println("Clicked!");
    pos = 0;
  }

  if ((pos != oldpos) && (pos >= 0)) {
    
    for (int i = 0; i < 8; i++) {
      if (i < pos) leds.set(i, BLUE, 10);
      else leds.set(i, OFF, 10);      
    }
    leds.show();
  }

  oldpos = pos;
}
