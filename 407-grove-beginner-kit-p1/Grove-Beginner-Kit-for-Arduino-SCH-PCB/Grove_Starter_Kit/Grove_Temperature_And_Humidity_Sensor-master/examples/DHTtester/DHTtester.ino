// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

/*Notice: The DHT10 is different from other DHT* sensor ,it uses i2c interface rather than one wire*/
          /*So it doesn't require a pin.*/

//#define DHTTYPE DHT10

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{

    SERIAL.begin(115200); 
    SERIAL.println("DHTxx test!");
    Wire.begin();

    /*if using WIO link,must pull up the power pin.*/
    // pinMode(PIN_GROVE_POWER, OUTPUT);
    // digitalWrite(PIN_GROVE_POWER, 1);

    dht.begin();
}

void loop() 
{
    float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    
    
    if(!dht.readTempAndHumidity(temp_hum_val)){
        SERIAL.print("Humidity: "); 
        SERIAL.print(temp_hum_val[0]);
        SERIAL.print(" %\t");
        SERIAL.print("Temperature: "); 
        SERIAL.print(temp_hum_val[1]);
        SERIAL.println(" *C");
    }
    else{
       SERIAL.println("Failed to get temprature and humidity value.");
    }

   delay(1500);
}
