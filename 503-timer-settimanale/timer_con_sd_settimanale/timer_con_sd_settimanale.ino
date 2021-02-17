#include "RTClib.h"
RTC_DS3231 rtc;
DateTime now;
unsigned long t1, dt;

/* SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 
 **/
#include <SPI.h>
#include <SD.h>
File datafile;
String fname = "weekly.txt";

char line[30];
int row[8];

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    /***
     * The abort() function causes abnormal program termination to occur. 
     * This realization disables interrupts and jumps to _exit() 
     * function with argument equal to 1. In the limited AVR environment, 
     * execution is effectively halted by entering an infinite loop. 
     */
    abort();
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    abort();
  }

  writedata();  
}

void loop() {
  dt = millis() - t1;
  if (dt > 500) {
    now = rtc.now();
    readdata();
    printdata();   
    t1 = millis();
  }
}

void writedata() {
  SD.remove(fname);
  datafile = SD.open(fname, FILE_WRITE);
  if (datafile) {
    //il primo valore è il giorno della settimana
    //Con l'* indico tutti i giorni/ore/minuti
    /*datafile.println("l;18;00;00;9;1");
    datafile.println("l;18;00;10;9;0");
    datafile.println("*;18;00;00;9;1");
    datafile.println("*;18;00;10;9;0");
    */
    datafile.println("*;*;*;00;9;1");//ogni giorno, ogni ora, ogni minuto
    datafile.println("*;*;*;10;9;0");
    datafile.close();
    Serial.println("done.");
  } else {    
    Serial.println("error writing");
  }  
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
  while (token != NULL){
    int n = 0;    
    if (i == 0) { //decode della prima cella: il giorno      
      n = decodeday(token);
    } else if (i == 1) { //ore
      n = decodehour(token);
    } else if (i == 2) { //minuti
      n = decodeminute(token);
    } else {
      n = atoi(token);  
    }    
    Serial.print(n); Serial.print(" ");
    row[i] = n;
    i++;
    token = strtok(NULL, ";");
  }
  Serial.print("\n");
  //verifico se devo attivare qualcosa...
  if ((now.dayOfTheWeek() == row[0]) &&
    (now.hour() == row[1]) &&
    (now.minute() == row[2]) &&
    (now.second() == row[3])
    ){
     //Serial.println("evento");
     digitalWrite(row[4], row[5]);      
  }
}

void printdata(){
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);    
    Serial.print(" - ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
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
