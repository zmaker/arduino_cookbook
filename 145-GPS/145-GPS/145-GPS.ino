#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS.h> 

float lat = 0.0,lon = 0.0; // create variable for latitude and longitude object  

SoftwareSerial gpsSerial(3,4);//rx,tx 

TinyGPS gps; // create gps object 

void setup(){ 
  Serial.begin(9600); // connect serial 
  Serial.println("Ready"); 
  gpsSerial.begin(9600); // connect gps sensor   
} 
void loop(){ 
  while (gpsSerial.available()){   
    char c = gpsSerial.read();   
    Serial.print(c);
    if (gps.encode(c)) {  
      gps.f_get_position(&lat,&lon); // get latitude and longitude 
      
      Serial.print("Position: "); 
      Serial.print("Latitude:"); 
      Serial.print(lat,6); 
      Serial.print(";"); 
      Serial.print("Longitude:"); 
      Serial.println(lon,6);     
    } 
  } 

/*
  String latitude = String(lat,6); 
  String longitude = String(lon,6); 
  Serial.println(latitude+";"+longitude); 
  */
  delay(1000); 
} 
