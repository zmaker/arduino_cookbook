#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();


void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
  lcd.print("hello, world!");

  //sensore BMP280
  bmp.begin(0x76, 0x60);
  
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //bmp_temp->printSensorDetails();
}

void loop() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(temp_event.temperature);

  lcd.setCursor(0, 1);
  lcd.print(pressure_event.pressure);
   
  delay(2000);
}
