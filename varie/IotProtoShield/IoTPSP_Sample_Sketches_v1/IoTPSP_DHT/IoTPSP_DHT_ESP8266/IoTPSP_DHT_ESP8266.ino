// program to test a DHT module or DHT naked sensor on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number

/*ESP8266 pinout names and GPIOs
 * 
 * GPIO  PIN NAME  NOTES
 * ADC0  A0
 * 0   D3      BOOT FAILURE if PULLED LOW
 * 1   TX      BOOT FAILURE if PULLED LOW
 * 2   D4      BOOT FAILURE if PULLED LOW
 * 3   RX
 * 4   D2      also used as I2C SDA
 * 5   D1      also used as I2C SCL
 * 12    D6      High On BOOT. also used as SPI MISO
 * 13    D7      High On BOOT, also used as SPI MOSI
 * 14    D5      SPI SCLK
 * 15    D8      BOOT FAILURE if PULLED HIGH, also used as SPI CS
 * 16    D0      High On BOOT, also used to Wake device from deep sleep
 * 
 * 
 * */


// this sketch needs DHT sensor library for ESPx

#include <DHT.h>;

//Constants
#define DHT_PIN 0         // ESP8266 data pin connecte dto DHT sensor
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
