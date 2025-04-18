#include "MyLD2410.h"

MyLD2410 sensor(Serial1);

void setup() {
  Serial.begin(115200);
  Serial1.begin(LD2410_BAUD_RATE, SERIAL_8N1);

  delay(2000);
  Serial.println("LD2410");

  if (!sensor.begin()) {
    Serial.println("LD2410 non trovato");
    while (true);
  }

  sensor.enhancedMode(false);
}

unsigned long t1;

void loop() {
  if (((millis() - t1) > 1000) && (sensor.check() == MyLD2410::Response::DATA) ) {
    
    Serial.print(sensor.statusString());

    if (sensor.presenceDetected()) {
      Serial.print(" dist: ");
      Serial.print(sensor.detectedDistance());
      Serial.println("cm ");
    }

    if (sensor.movingTargetDetected()) {
      Serial.print("moving: ");
      Serial.print(sensor.movingTargetSignal() );
      Serial.print("@");
      Serial.print(sensor.movingTargetDistance() );
      Serial.println("cm");
    }

    if (sensor.stationaryTargetDetected()) {
      Serial.print("stat: ");
      Serial.print(sensor.stationaryTargetSignal() );
      Serial.print("@");
      Serial.print(sensor.stationaryTargetDistance() );
      Serial.println("cm");
    }

    if (sensor.getFirmwareMajor() > 1) {
      Serial.print("Light: ");
      Serial.print(sensor.getLightLevel() );
      Serial.print(" Out:");
      Serial.println(sensor.getOutLevel() );
    }

    t1 = millis();
  }

}
