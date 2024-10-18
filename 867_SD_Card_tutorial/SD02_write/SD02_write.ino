/*
  SD card read
 ** SDO - pin 11
 ** SDI - pin 12
 ** CLK - pin 13
 ** CS - pin 10
*/
#include <SD.h>

#define CS_PIN 10
File myFile;

void setup() {
  Serial.begin(9600);

  if (!SD.begin(CS_PIN)){
    Serial.println("initialization failed. ");
    while (true);
  }

  Serial.println("write sd");

  //apro il file in scrittura
  myFile = SD.open("/filetest.txt", FILE_WRITE); //8.3 
  if (myFile) {
    myFile.println("1. Hello File!!");
    myFile.println("2. Hello File!!");

    myFile.close();
    Serial.println("scrittura completa");
  } else {
    Serial.println("non apro il file");
  }
}

void loop() {}
