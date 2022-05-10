// program to test an RTC module on the IoT Proto Shield Plus
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
  

// this skecth uses the adafriut RTClib https://github.com/adafruit/RTClib

#include "RTClib.h"

#define SET_TIME_FROM_HOST_PC //comment this line if your DS3231 has a battery and the time and and has already been set

RTC_DS3231 rtc; //define the rtc object

void setup () {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

#ifdef SET_TIME_FROM_HOST_PC
  // the following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //set the time and date on the DS3231
#endif
  
}



void loop () {
    DateTime now = rtc.now();

    Serial.print("Date red from RTC module: ");
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.println();

    Serial.print("Time red from RTC module: ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print("Temperature red from RTC module: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    delay(3000);
}
