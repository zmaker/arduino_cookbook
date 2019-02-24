/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino MKR 1010
  to connect your project to Blynk.

  Note: This requires WiFiNINA library
    from http://librarymanager/all#WiFiNINA

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "43ea4face364826782482346";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "www.zeppelinmaker.it";
char pass[] = "45645465465";

void setup() {  
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass); 
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1) { //ricevo dall'app
  int n = param.asInt();
  /*
    param.asInt();    // get value as an Integer
    param.asFloat();  // get value as a Float
    param.asDouble(); // get value as a Double
    param.asStr();
  */
  
  Serial.print("V1 Slider value is: ");
  Serial.println(n);
  if ( n >= 100 ) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);  
  }
}
