// I2C device class (I2Cdev) demonstration Arduino sketch for AK8975 class
#include "Wire.h"
#include "I2Cdev.h"
#include "AK8975.h"
#include "MPU6050.h"

AK8975 mag(0x0C);  //indirizzo del sensore
MPU6050 accelgyro;

#define LED_PIN 13

void setup() {    
    Wire.begin();
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    
    //init del modulo MPU (va fatto prima di usare la bussola che è collegata 
    accelgyro.initialize();
    accelgyro.setI2CBypassEnabled(true);
    mag.initialize();

    //verifica comunicazione
    while (mag.testConnection()) {
      Serial.print(".");
    }
    Serial.println("\nAK8975 connessa!");    
}

int16_t mx, my, mz;

void loop() {
    //legge i dati grezzi
    mag.getHeading(&mx, &my, &mz);

    //calcolo angolo:
    float heading = atan2((double)my, (double)mx) * 180.0/3.14159265 + 180;
    while (heading < 0) heading += 360;
    while (heading > 360) heading -= 360;
    
    //arrotondo all'unità
    int angolo = (int)heading;
    
    Serial.print(heading);
    Serial.print(" (");
    Serial.print(angolo);
    Serial.println(") °");

    //il led si accende quando la bussola è puntata a nord
    if ((angolo <= 5) || (angolo >= 360)) {
      digitalWrite(LED_PIN, HIGH);  
    } else { 
      digitalWrite(LED_PIN, LOW);
    } 
    
    delay(100); 
}
