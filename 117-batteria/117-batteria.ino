/*
 https://forum.mysensors.org/topic/186/new-library-to-read-arduino-vcc-supply-level-without-resistors-for-battery-powered-sensor-nodes-that-do-not-use-a-voltage-regulator-but-connect-directly-to-the-batteries
 
 */
#include <Vcc.h>

const float minVcc = 0.0;
const float maxVcc = 5.0;
const float fix = 4.9/5.0;

Vcc vcc(fix);

void setup() {
  Serial.begin(9600);

}

void loop() {
  float v = vcc.Read_Volts();
  Serial.print("V=");
  Serial.print(v);

  float p = vcc.Read_Perc(minVcc, maxVcc);
  Serial.print(" Perc=");
  Serial.println(p);
}




