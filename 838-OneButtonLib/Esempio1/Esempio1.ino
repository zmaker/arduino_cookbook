#include <OneButton.h>

OneButton button(2, false); //false = pulldown

static void singleClick();

void setup() {
  Serial.begin(115200);
  Serial.println("OneButton");

  pinMode(4, OUTPUT);

  button.setDebounceMs(20);
  button.attachClick(singleClick);
  button.attachDoubleClick(
    [](){
      Serial.println("Double clic");
    }
  );
}

void loop() {
  button.tick();
}

static void singleClick(){
  Serial.println("Clicked!");
  digitalWrite(4, !digitalRead(4));
}
