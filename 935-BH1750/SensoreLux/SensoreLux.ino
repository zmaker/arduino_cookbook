#include <BH1750.h>

BH1750 sensor;
bool SENSOR_READY;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("BH1750");

  Wire.begin();
  //0x23
  //0x5c
  //lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)
  /*
  BH1750_CONTINUOUS_LOW_RES_MODE
  BH1750_CONTINUOUS_HIGH_RES_MODE (default)
  BH1750_CONTINUOUS_HIGH_RES_MODE_2

  BH1750_ONE_TIME_LOW_RES_MODE
  BH1750_ONE_TIME_HIGH_RES_MODE
  BH1750_ONE_TIME_HIGH_RES_MODE_2
  */
  SENSOR_READY = sensor.begin();
}

void loop() {
  if (SENSOR_READY) {
    float lux = sensor.readLightLevel();
    Serial.print("lux: ");Serial.print(lux);
    Serial.println(" lx.");
  }
  delay(1000);
}
