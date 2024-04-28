#include <OneButton.h>

OneButton button(2, false); //false = pulldown

static void ledOn();
static void ledOff(void *oneButton);

void setup() {
  Serial.begin(115200);
  Serial.println("OneButton");

  pinMode(4, OUTPUT);

  button.setDebounceMs(20);
  button.setPressMs(800);

  button.attachClick(ledOn);

  button.attachLongPressStart(
    [](void *oneButton){ Serial.println("START"); }, &button
  );
  button.attachDuringLongPress(
    [](void *oneButton){ Serial.print("."); }, &button
  );
  button.attachLongPressStop(ledOff, &button);
}

void loop() {
  button.tick();
}

static void ledOn(){
  Serial.println("ON");
  digitalWrite(4, HIGH);
}

static void ledOff(void *oneButton){
  Serial.println("\nOFF");
  digitalWrite(4, LOW);
}
