#include "secrets.h"
#include <WiFiNINA.h>  
#include <PubSubClient.h>

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 68, 108);
PubSubClient client(wifi);

unsigned long t1, dt;
int stato = 0;

void setup() {
  while (!Serial){
    ;  
  }
  Serial.begin(9600);
  Serial.println("OK");
  Serial.print("Connessione...");
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WiFi!\n");

  client.setServer(server, 1883);

  if (client.connect("arduinopub")) {
    Serial.println("mqtt connected");
    client.subscribe("/hello");
  } else {
    Serial.println("mqtt not connected");
    Serial.print("failed, rc=");
    Serial.println(client.state());
  }
  t1 = millis();
}

void loop() {
  dt = millis() - t1;
  if (dt > 2000) {
    if ( (stato%2) == 0) {
      client.publish("/hello", "on");  
      Serial.println("on");
    } else {
      client.publish("/hello", "off");  
      Serial.println("off");
    }
    stato++;
    t1 = millis();
  }
}
