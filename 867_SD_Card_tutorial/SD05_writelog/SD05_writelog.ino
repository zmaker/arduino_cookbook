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
  Serial.println("esempio log");

  //composizione nome file usando la data (serve un RTC)
  int anno = 2024;
  int mese = 9;
  int giorno = 1;
  char nomefile[15];
  sprintf(nomefile, "/%04d%02d%02d.LOG", anno, mese, giorno);
  Serial.print("log name: ");Serial.println(nomefile);

  //apro il file in scrittura
  myFile = SD.open(nomefile, FILE_WRITE); //8.3 
  if (myFile) {
    //compongo i dati usando le info di hh/mm/ss
    int val = analogRead(A0);
    int hh = 12;
    int mi = 34;
    int ss = 9;
    char data[30];
    sprintf(data, "%02d:%02d:%02d;temp;%d", hh, mi, ss, val);
    Serial.print("riga: ");Serial.println(data);

    //mi sposto in fondo al file
    myFile.seek(EOF);
    myFile.println(data);    
    myFile.close();
  } else {
    Serial.println("non apro il file");
  }

  Serial.println("\nlettura log");
  myFile = SD.open(nomefile); //8.3 
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

