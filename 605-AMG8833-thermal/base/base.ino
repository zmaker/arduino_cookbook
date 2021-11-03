#include <Melopero_AMG8833.h>

Melopero_AMG8833 sensor;

void setup() {
  Serial.begin(9600);

  // initializing I2C to use default address AMG8833_I2C_ADDRESS_B and Wire (I2C-0):
  Wire.begin();
  sensor.initI2C();
  // To use Wire1 (I2C-1): /0x69
  // Wire1.begin();
  // sensor.initI2C(AMG8833_I2C_ADDRESS_B, Wire1);

  Serial.print("Resetting sensor ... ");  
  int statusCode = sensor.resetFlagsAndSettings();
  Serial.println(sensor.getErrorDescription(statusCode));

  Serial.print("Setting FPS ... ");
  statusCode = sensor.setFPSMode(FPS_MODE::FPS_10);
  Serial.println(sensor.getErrorDescription(statusCode));
}

void loop() {
  //Updating thermistor temperature ... ");
  if (sensor.updateThermistorTemperature() == 0) {
    //se è 0 è ok...
    //Serial.println(sensor.getErrorDescription(statusCode));
    //Serial.println(statusCode);
    
    //"Updating pixel matrix ... ");
    if (sensor.updatePixelMatrix() == 0) {
      Serial.print("Temp: ");
      Serial.print(sensor.thermistorTemperature);
      Serial.println("°C");

      for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
          Serial.print(sensor.pixelMatrix[y][x]);
          Serial.print(" ");
        }
        Serial.println();
      }
    }
  }

  delay(1000);
}
