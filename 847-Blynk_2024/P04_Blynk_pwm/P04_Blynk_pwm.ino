#import "secrets.h"

#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "...."
#define BLYNK_TEMPLATE_NAME "ProgettoTutorial"
#define BLYNK_AUTH_TOKEN "..."

#include <SPI.h>
#include <WiFiS3.h>
#include <BlynkSimpleWifi.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int button = LOW;
BlynkTimer timer;

BLYNK_WRITE(V6){
  int pwm = param.asInt();
  analogWrite(6, pwm);
}

void myTimer() {
  Blynk.virtualWrite(V3, button);
  int val = analogRead(A0);
  Blynk.virtualWrite(V0, val);
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