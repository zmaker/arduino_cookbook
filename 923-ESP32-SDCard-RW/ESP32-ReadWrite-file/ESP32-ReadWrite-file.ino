#include <SPI.h>
#include <SD.h>

void setup() {
  Serial.begin(115200);

  if (!SD.begin(5)) {
    Serial.println("errore sd: check collegamenti o formato");
    while(true);
  }

  //scrittura file di testo
  Serial.println("SCRITTURA FILE: ");
  File file = SD.open("/file01.txt", FILE_WRITE);
  if (file) {
    file.println("Hello esp32");
    file.println("riga 2");
    file.close();
  } else {
    Serial.println("errore file: non riesco a crearlo");
  }

  //lettura dile di testo
  File fr = SD.open("/file01.txt");
  if (fr) {
    Serial.println("\nLETTURA FILE: ");
    while(fr.available()) {
      Serial.write(fr.read());
    }
    fr.close();
  } else {
    Serial.println("errore file: non riesco a leggerlo");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
