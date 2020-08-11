// This example USES the ADC function.

#include "LIS3DHTR.h"
LIS3DHTR<TwoWire> LIS; //SPI
void setup()
{
  Serial.begin(115200);
  while (!Serial);
  LIS.begin(SPI, 10); //SPI SS/CS
  delay(100);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_4G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_8G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_16G);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_10HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_200HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1_6KHZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_5KHZ);
}
void loop() {
    if (!LIS) {
        Serial.println("LIS3DHTR didn't connect.");
        while (1);
        return;
    }
    //ADC
    Serial.print("adc1:"); Serial.println(LIS.readbitADC1());
    Serial.print("adc2:"); Serial.println(LIS.readbitADC2());
    Serial.print("adc3:"); Serial.println(LIS.readbitADC3());
    delay(500);
}
