#define SIMULATO
#define DEBUG


#ifndef SIMULATO
  //dichiarazione sonda PT100
  #include <Adafruit_MAX31865.h>
  Adafruit_MAX31865 thermo = Adafruit_MAX31865(4,5,6,7);
#endif

int temp;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  #ifndef SIMULATO
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  #endif
}

void loop() {

  //misuro temp con MAX31865
    #ifndef SIMULATO
    temp = thermo.temperature(100, RREF);
    #else
    temp = (float)(map(analogRead(A1), 0, 1023, 500, 10000)) / 100.0f;
    #endif
  
  #ifdef DEBUG
  Serial.println(temp);
  #else
  //stampo su display
  #endif
    
    delay(100);
   
}
