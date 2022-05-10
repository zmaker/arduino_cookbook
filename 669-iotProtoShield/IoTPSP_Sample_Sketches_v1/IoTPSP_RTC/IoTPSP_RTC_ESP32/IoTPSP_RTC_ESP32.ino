// program to test a RTC module on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number


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
