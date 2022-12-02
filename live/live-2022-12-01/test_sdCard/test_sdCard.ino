#include "FS.h"
#include "SD.h"
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Test SD Card");

  Serial.print("Initializing SD card..."); 
  delay(2000);
  if (!SD.begin(5)){
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("Initializing SD: OK"); 

  File f = SD.open("/test.txt", FILE_WRITE);
  if (f) {
    Serial.println("Writing to test.txt...");
    f.print("sens: ");
    int v = analogRead(34);
    f.println(v);

    f.close();
    Serial.println("Writing: ok");
  }  else {
    Serial.println("Non apro il file");
  }

  Serial.println("Leggo file");
  f = SD.open("/test.txt", FILE_READ);
  if (f) {
    while(f.available()) {
      Serial.write(f.read());
    }
    
    f.close();    
  } else {
    Serial.println("Non apro il file");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
