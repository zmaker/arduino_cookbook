// program to test a DFPlayer Mini MP3 module on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number
 

#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;


void setup()
{
  Serial.begin(9600);

  myDFPlayer.begin(Serial);


  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
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
