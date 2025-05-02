/*
 * @url  https://github.com/DFRobot/DFRobot_SHT20
https://wiki.dfrobot.com/SHT20_I2C_Temperature_%26_Humidity_Sensor__Waterproof_Probe__SKU__SEN0227
*/

#include "DFRobot_SHT20.h"

DFRobot_SHT20 sens(&Wire, SHT20_I2C_ADDR);

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("SHT20");

  sens.initSHT20();
}

void loop() {
  float temp = sens.readTemperature();
  float hum = sens.readHumidity();  

  Serial.print("t: ");Serial.print(temp);
  Serial.print("\th: ");Serial.println(hum);
  delay(2000);
}
