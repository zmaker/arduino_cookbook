/*
  SD card read
 ** SDO - pin 11
 ** SDI - pin 12
 ** CLK - pin 13
 ** CS - pin 10
*/
#include <SD.h>

//#define per il pn di CS - verifica il tuo hardware
#define CS_PIN 10
File myFile;

void setup() {
  Serial.begin(9600);
  //init della scheda sd
  if (!SD.begin(CS_PIN)){
    Serial.println("initialization failed. ");
    while (true);
  }
  Serial.println("read sd");
  //apro il file in lettura
  myFile = SD.open("/filetest.txt"); //8.3 
  if (myFile) {
    while(myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("non apro il file");
  }

}

void loop() {}

