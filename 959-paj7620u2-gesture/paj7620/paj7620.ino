#include <DFRobot_PAJ7620U2.h>
DFRobot_PAJ7620U2 paj;

// lib lcd di Stefan Staub
#include <LCDi2c.h>
LCDi2c lcd(0x27, Wire);

void setup() {
  Serial.begin(9600);

  lcd.begin(2, 16);
  lcd.display(DISPLAY_ON);
  lcd.display(BACKLIGHT_ON);
  lcd.cls();
  lcd.locate(1,1);
  lcd.printf("PAJ7620U2");

  if (paj.begin() != 0) {
    lcd.locate(2,1);
    lcd.printf("ERR sensore");
    while(true);
  }

  paj.setGestureHighRate(true);

}

void loop() {
  DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();
  if (gesture != paj.eGestureNone) {
    String txt = paj.gestureDescription(gesture);
    Serial.print(gesture);
    Serial.print("\t");
    Serial.println(txt);

    lcd.cls();
    lcd.locate(2,1);
    lcd.printf(txt.c_str());
  }

}
