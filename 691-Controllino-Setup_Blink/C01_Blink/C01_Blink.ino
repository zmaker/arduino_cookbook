// https://raw.githubusercontent.com/CONTROLLINO-PLC/CONTROLLINO_Library/master/Boards/package_ControllinoHardware_index.json

#include <Controllino.h> 

void setup() {
  pinMode(CONTROLLINO_DO0, OUTPUT);
  pinMode(CONTROLLINO_R0, OUTPUT);

}

void loop() {
  digitalWrite(CONTROLLINO_DO0, HIGH);
  digitalWrite(CONTROLLINO_R0, LOW);
  delay(1000);
  digitalWrite(CONTROLLINO_DO0, LOW);
  digitalWrite(CONTROLLINO_R0, HIGH);
  delay(1000);
}
