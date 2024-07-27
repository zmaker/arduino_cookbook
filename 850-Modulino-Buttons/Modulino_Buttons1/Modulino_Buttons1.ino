#include <Modulino.h>

ModulinoButtons bt;

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
    } else if (bt.isPressed(1)) {
      Serial.println("B");
    } else if (bt.isPressed(2)) {
      Serial.println("C");
    }
  }
}
