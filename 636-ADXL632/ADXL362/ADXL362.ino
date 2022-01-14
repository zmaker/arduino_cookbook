/*
 ADXL362
 
 for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet
 
 SCL -> 13
 SDA -> 11
 SDO -> 12
 CS  -> 10

 library: https://github.com/annem/ADXL362
*/ 

#include <SPI.h>
#include <ADXL362.h>

ADXL362 sens;

int x,y,z,t;

void setup(){  
  Serial.begin(9600);
  sens.begin(10);
  sens.beginMeasure();
  Serial.println("ADXL362");
}

void loop(){
  sens.readXYZTData(x,y,z,t);  
  Serial.print("x:");
  Serial.print(x);	 
  Serial.print("\ty:");
  Serial.print(y);	 
  Serial.print("\tz:");
  Serial.print(z);	 
  Serial.print("\tt:");
  Serial.println(t);	 
  delay(100); 
}
