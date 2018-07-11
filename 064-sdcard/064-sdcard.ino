/*
  Creare un file su SD Card

  Usa l'interfaccia SPI con le connessioni:
  MOSI - pin 11
  MISO - pin 12
  CLK - pin 13
  CS - pin 10 (con la datalogger shield)
*/

#include <SPI.h>
#include <SD.h>

File file;

void setup() {
  Serial.begin(9600);
  if (!SD.begin(10)) {
    Serial.println("Errore SD");
    return;
  }
  Serial.println("SD pronta");

  if (SD.exists("example.txt")) {
    SD.remove("example.txt");
  } 

  Serial.println("creo un file");  
  file = SD.open("example.txt", FILE_WRITE);
  file.write("hello!");
  file.close();

}

void loop() {  
}
