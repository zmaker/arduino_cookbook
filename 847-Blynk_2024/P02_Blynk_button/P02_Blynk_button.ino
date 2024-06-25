#import "secrets.h"

#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL4qQTsMxVz"
#define BLYNK_TEMPLATE_NAME "ProgettoTutorial"
#define BLYNK_AUTH_TOKEN "6RNuhsQdjLmlNBm84gDlgKvs8yqO_iwb"

#include <SPI.h>
#include <WiFiS3.h>
#include <BlynkSimpleWifi.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int button = LOW;
BlynkTimer timer;

void myTimer() {
  Blynk.virtualWrite(V3, button);
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Blynk Arduino R4 WiFi");

  pinMode(2, OUTPUT);
  pinMode(3, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimer);
}

void loop() {
  button = digitalRead(3);
  Blynk.run();
  timer.run();
}