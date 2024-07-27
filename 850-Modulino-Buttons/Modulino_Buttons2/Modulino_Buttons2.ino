#include <Modulino.h>

ModulinoButtons bt;

boolean led[3] = {false, false, false};

void setup() {
  Serial.begin(115200);
  delay(2000);

  Modulino.begin();
  bt.begin();
}

void loop() {
  if (bt.update()) {
    if (bt.isPressed(0)) {
      Serial.println("A");
      led[0] = !led[0];
    } else if (bt.isPressed(1)) {
      Serial.println("B");
      led[1] = !led[1];
    } else if (bt.isPressed(2)) {
      Serial.println("C");
      led[2] = !led[2];
    }

    bt.setLeds(led[0], led[1], led[2]);
  }
}
