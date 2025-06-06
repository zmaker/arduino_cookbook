#include <SPI.h>
#include <SD.h>

void setup() {
  Serial.begin(115200);

  if (!SD.begin(5)) {
    Serial.println("errore sd");
    while(true);
  }
}

void loop() {
  int val = analogRead(12);
  unsigned long ts = millis();

  Serial.print("val: ");Serial.println(val);
  File f = SD.open("/log.txt", FILE_APPEND);
  if (f) {
    f.print(ts);
    f.print("; ");
    f.println(val);
    f.close();
  } else {
    Serial.println("errore scrittura");
  }

  Serial.println("-----------------");
  File fr = SD.open("/log.txt");
  if (fr) {
    while (fr.available()) {
      Serial.write(fr.read());
    }
    fr.close();
  }

  delay(10000);
}
