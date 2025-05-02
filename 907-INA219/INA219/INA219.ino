#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 sens;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("INA219");

  if (!sens.begin()) {
    Serial.println("INA219 KO");
    while(true);
  }

  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();
}

void loop() {
  float vs = sens.getShuntVoltage_mV();
  float ia = sens.getCurrent_mA();
  float pow = sens.getPower_mW();

  Serial.print("vs: ");Serial.print(vs);
  Serial.print("\tia: ");Serial.print(ia);
  Serial.print("\tpow: ");Serial.println(pow);
  delay(2000);
}
