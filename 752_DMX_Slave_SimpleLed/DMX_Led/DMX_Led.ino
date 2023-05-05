/*
http://www.cqrobot.wiki/index.php/DMX_Shield_for_Arduino_SKU:_AngelDFR0260US
https://sourceforge.net/projects/dmxlibraryforar/
http://www.cqrobot.wiki/images/1/14/DMX_Shield_User_manual.pdf

software
https://www.qlcplus.org/downloads.php
https://www.qlcplus.org/docs/html_en_EN/tutorial.html

*/

#include <Conceptinetics.h>
#define MY_DMX_ADDRESS 1
#define MY_DMX_CHANNELS 2
#define RXEN_PIN 2

DMX_Slave dmxslave(MY_DMX_CHANNELS, RXEN_PIN);

void setup() {
  pinMode(13, OUTPUT);
  dmxslave.enable();
  dmxslave.setStartAddress(MY_DMX_ADDRESS);
}

void loop() {
  int v1 = dmxslave.getChannelValue(1);
  analogWrite(10, v1);
  
  int v2 = dmxslave.getChannelValue(2);
  if (v2 > 127) {
    digitalWrite(13, HIGH);  
  } else {
    digitalWrite(13, LOW);  
  }
}
