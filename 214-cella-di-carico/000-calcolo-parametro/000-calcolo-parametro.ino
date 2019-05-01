/**
 * 
 * How to Calibrate Your Scale

https://www.instructables.com/id/How-to-Interface-HX711-Balance-Module-With-Load-Ce/

1. Call set_scale() with no parameter.
2. Call tare() with no parameter.
3. Place a known weight on the scale and call get_units(10).
4. Divide the result in step 3 to your known weight. You should get about the parameter you need to pass to set_scale.
5. Adjust the parameter in step 4 until you get an accurate reading.
 */

#include "HX711.h"

HX711 scale(2, 3);

void setup() {
  Serial.begin(9600);
 
  scale.set_scale();
  scale.tare();

  Serial.println("peso 100gr e premi tasto");
  while (!Serial.available()) {}

  float cal = scale.get_units(10);
  float peso = 100.0f;  //100gr
  float scale_par = cal / peso;
  
  Serial.print("cal: ");
  Serial.println(scale_par);                 
}

void loop() {
  
}
