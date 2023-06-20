#include "AS726X.h"

AS726X sensor;

float r[7];

void setup() {
  Wire.begin();
  Serial.begin(9600);

  sensor.begin();

  if (sensor.getVersion() == SENSORTYPE_AS7262) {
    Serial.print("V\tB\tG\tY\tO\tR\tt\n");
  } else if (sensor.getVersion() == SENSORTYPE_AS7263) {
    Serial.print("R\tS\tT\tU\tV\tW\tt\n");
  } else {
    Serial.print("error\n");
    while(1);
  }

}

void loop() {
  sensor.takeMeasurements();
  if (sensor.getVersion() == SENSORTYPE_AS7262) {
    r[0] = sensor.getCalibratedViolet();
    r[1] = sensor.getCalibratedBlue();
    r[2] = sensor.getCalibratedGreen();
    r[3] = sensor.getCalibratedYellow();    
    r[4] = sensor.getCalibratedOrange();
    r[5] = sensor.getCalibratedRed();
    
  } else if (sensor.getVersion() == SENSORTYPE_AS7263) {
    r[0] = sensor.getCalibratedR();
    r[1] = sensor.getCalibratedS();
    r[2] = sensor.getCalibratedT();
    r[3] = sensor.getCalibratedU();
    r[4] = sensor.getCalibratedV();
    r[5] = sensor.getCalibratedW();    
  }
  r[6] = sensor.getTemperature();
  
  for (int i = 0; i <= 7; i++) {
    Serial.print(r[i]);  
    Serial.print("\t");
  }
  Serial.print("\n");
  delay(1000);
}
