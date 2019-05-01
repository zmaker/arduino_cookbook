#include "HX711.h"

HX711 scale(2, 3);

float calibration_factor = -1944; // this calibration factor is adjusted according to my load cell
float units;


void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0  
}

void loop() {
  scale.set_scale(calibration_factor); 

  Serial.print("Reading: ");
  units = scale.get_units(); 
  if (units < 0) {
    units = 0.00;
  }
  Serial.print(units);
  Serial.print(" g."); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available()) {
    char temp = Serial.read();
    if (temp == 'a') {
      calibration_factor += 10;
    } else if(temp == 'z') {
      calibration_factor -= 10;
    }
  }
}
