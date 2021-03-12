// sonda temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(2); //pin 2
DallasTemperature temp(&oneWire);

#include <Wire.h>
#include <Arduino.h>
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ 5);         

#include "RTClib.h"
RTC_DS3231 rtc;

DateTime now;
unsigned long t1, t2, dt;

/* SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 
 **/
#include <SPI.h>
#include <SD.h>
File datafile;
String fname = "termo.txt";

char line[30];
int row[8];

int currtemp = 14;
int progtemp = 14;
int soglia = 2;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    abort();
  }

  temp.begin();

  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();
}

void loop() {
  dt = millis() - t1;
  if (dt > 200) {
    displaytime();
    t1 = millis();
  }
  dt = millis() - t2;
  if (dt > 500) {
    now = rtc.now();
    temp.requestTemperatures();
    currtemp = (int)temp.getTempCByIndex(0);
    readdata();
    t2 = millis();
  }
  if (currtemp < progtemp - soglia) {
    digitalWrite(6, HIGH);
    digitalWrite(9, HIGH);
  } else if (currtemp > progtemp + soglia) {
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
  }
}

char datainfo[20];
char wdays[] = {'d','l','m','M','g','v','s'};

void displaytime() {
  u8x8.setCursor(0,0);
  char dw = wdays[now.dayOfTheWeek()];
  sprintf(datainfo, "%c %02d:%02d:%02d", dw, now.hour(), now.minute(), now.second());
  u8x8.print(datainfo);

  u8x8.setCursor(0,2);
  u8x8.print("T: ");
  u8x8.print(currtemp);  
  u8x8.print("C");
  u8x8.setCursor(0,3);
  u8x8.print("P: ");
  u8x8.print(progtemp);
  u8x8.print("C");
}

void readdata() {
  datafile = SD.open(fname);
  int i = 0;
  if (datafile) {
    while (datafile.available()) {
      char c = datafile.read();
      if (c == '\n') {
        line[i] = 0;
        //Serial.println(line);
        decodedata(line);
        i = 0;        
      } else if (c == '\r') {
        
      } else {
        line[i] = c;
        i++;  
      }
    }
    datafile.close();
  } else {    
    Serial.println("error opening file");
  }  
}

void decodedata(char* str){
  char* token = strtok(str, ";");
  int i = 0;
  while (token != NULL) {
    int n = 0;
    if (i == 0) {
      n = decodeday(token);  
    } else if (i == 1) { //ore
      n = decodehour(token);
    } else if (i == 2) { //minuti
      n = decodeminute(token);
    } else {
      //temperatura impostata
      n = atoi(token);  
    }  
    row[i] = n;
    i++;
    token = strtok(NULL, ";");
  }

  if (row[0] == now.dayOfTheWeek()) {
    unsigned long tc = (long)now.hour() * 3600l + (long)now.minute() * 60l + (long)now.second();
    unsigned long tr = (long)row[1] * 3600l + (long)row[2] * 60l + (long)row[3];

    if (tr <= tc) {
      progtemp = row[4];  
    }
  }
}

int decodeday(char* str){
  int n = 0;
  //d l m M g v s
  //0 1 2 3 4 5 6 
  char c = str[0];
  switch (c) {
    case '*':
      n = now.dayOfTheWeek();
      break;
    case 'd':
      n = 0;
      break;    
    case 'l':
      n = 1;
      break;    
    case 'm':
      n = 2;
      break;    
    case 'M':
      n = 3;
      break;    
    case 'g':
      n = 4;
      break;    
    case 'v':
      n = 5;
      break;    
    case 's':
      n = 6;
      break;
    default:
      n = -1;    
  }
  return n;
}

int decodehour(char* str){  
  int n = -1;
  if (strcmp(str, "*") == 0) {
    n = now.hour();
  } else {
    n = atoi(str);
  }
  return n;
}

int decodeminute(char* str){  
  int n = -1;
  if (strcmp(str, "*") == 0) {
    n = now.minute();
  } else {
    n = atoi(str);
  }
  return n;
}
