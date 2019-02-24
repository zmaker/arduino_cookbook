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
char auth[] = "43ea4face4644d1f8c5a0f167084cd31";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "www.zeppelinmaker.it";
char pass[] = "90557586035762543700";

BlynkTimer timer;

void setup() { 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);  
  timer.setInterval(500L, leggidati ); 
}

void loop() {
  Blynk.run();
  timer.run();
}

void leggidati() {
    int v = analogRead(A1);    
    Blynk.virtualWrite(V7, v);
}






