// http://mustcalculate.com/electronics/capacitorchargeanddischarge.php?vfrom=.3&vto=4.8&vs=5&c=1.5&r=10&time=

#include <EEPROM.h>
int reboot = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  
  //EEPROM.put(10, reboot);
  //delay(100);
  EEPROM.get(10, reboot);
  Serial.println(reboot);

  for (int i = 0; i < reboot*2; i++) {
    digitalWrite(13, !digitalRead(13));
    delay(200);
  }
  digitalWrite(13, LOW);

}

void loop() {
  if (digitalRead(2) == LOW) {
    digitalWrite(13, HIGH);
    reboot++;
    EEPROM.put(10, reboot);
    Serial.println("HALT");
    while(1);
  }  
}
