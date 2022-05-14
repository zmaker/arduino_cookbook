// program to test a DHT module or DHT naked sensor on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

// this sketch needs DHT sensor library ESPx 

#include <DHT.h>;

//Constants
#define DHT_PIN 13         // ESP32 data pin connecte dto DHT sensor
#define DHT_TYPE DHT22    // DHT 22
DHT dht(DHT_PIN, DHT_TYPE);


//Variables
int chk;
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

void setup()
{
  Serial.begin(9600);
  delay(300);
  Serial.println("IoTPSP humidity and temperature with DHT22");

  
  dht.begin();
  delay(2000);
}

void loop()
{

  //Read data and store it to variables hum and temp
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temp: ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(2000);
}
