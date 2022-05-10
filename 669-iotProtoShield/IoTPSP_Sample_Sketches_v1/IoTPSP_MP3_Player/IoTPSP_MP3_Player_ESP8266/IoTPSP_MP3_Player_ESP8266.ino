// program to test a module on the IoT Proto Shield Plus
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
  
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 0); // Set GPIO2 to RX, set GPIO0 TX
DFRobotDFPlayerMini myDFPlayer; //define MP3 player object


void setup()
{
  mySoftwareSerial.begin(9600); //Use softwareSerial to communicate with MP3 player

  myDFPlayer.begin(mySoftwareSerial); //start communication with MP3 player

  myDFPlayer.volume(20);  //Set volume value: From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }

}
