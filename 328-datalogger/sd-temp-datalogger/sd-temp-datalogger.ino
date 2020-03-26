#include <Wire.h>
//RTCLib by Neiro
#include "RTClib.h"
DS1307 rtc;

#include <SimpleDHT.h>
// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
#define _DHTPIN 2
SimpleDHT22 dht22(_DHTPIN);

/*
SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 
*/
//SD card SPI
#include <SPI.h>
#include <SD.h>
File logfile;

void setup () {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  //sdcard
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
}

float temp, hum;

void loop () {
  DateTime now = rtc.now();

  dht22.read2(&temp, &hum, NULL);
     
  logdata(now, temp, hum); 
  
  delay(5000);
}

void logdata(DateTime now, float t, float h){

  String msg =
    String(now.year())+"/"+
    String(pad2(now.month()))+"/"+
    String(pad2(now.day()))+" "+
    String(pad2(now.hour()))+":"+
    String(pad2(now.minute()))+":"+
    String(pad2(now.second()))+" "+
    "t: "+String(t)+"C\t"+
    "h: "+String(h)+"%";
        
  Serial.println(msg);
    
  logfile = SD.open("templog.txt", FILE_WRITE);
  if (logfile) {
    logfile.println(msg);    
    logfile.close();
  } 
 
}

String pad2(int n) {
  String ret = "";
  if (n < 10) ret = "0"+String(n);
  else ret = String(n);
  return ret;
}
