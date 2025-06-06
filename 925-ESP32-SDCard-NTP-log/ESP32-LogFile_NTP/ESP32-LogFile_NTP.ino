#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <time.h>

const char* ssid = "www.zeppelinmaker.it";
const char* password = "*1000balene";
const char* ntpServer = "pool.ntp.org";

const char* tz = "CET-1CEST,M3.5.0/2,M10.5.0/3"; 

unsigned long t1; 
struct tm timeinfo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso");

  configTzTime(tz, ntpServer);

  while (!getLocalTime(&timeinfo)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nNTP sincro.");

  if (!SD.begin(5)) {
    Serial.println("Errore SD.");
    while(true);
  }

  t1 = millis();
}



void loop() {
  if ((millis() - t1) > 5000) {
    
    if (getLocalTime(&timeinfo)) {
      char dataora[30];
      strftime(dataora, sizeof(dataora), "%Y-%m-%d %H:%M:%S", &timeinfo); 
      Serial.println(dataora);
      
      int val = analogRead(2);

      File f = SD.open("/datalog.txt", FILE_APPEND);
      if (f) {
        f.print(dataora);
        f.print(", ");
        f.println(val);
        f.close();
      }

      Serial.println("-----------------");
      File fr = SD.open("/datalog.txt");
      if (fr) {
        while (fr.available()) {
          Serial.write(fr.read());
        }
        fr.close();
      }
    }
    t1 = millis();
  }

}
