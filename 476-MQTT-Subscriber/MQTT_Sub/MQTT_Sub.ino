#include "secrets.h"
#include <WiFiNINA.h>  
#include <PubSubClient.h>

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 68, 108);
PubSubClient client(wifi);

void setup() {
  pinMode(6, OUTPUT);
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
  client.setCallback(callback);

  if (client.connect("arduinosub")) {
    Serial.println("mqtt connected");
    client.subscribe("/hello");
  } else {
    Serial.println("mqtt not connected");
    Serial.print("failed, rc=");
    Serial.println(client.state());
  }

}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length){
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];  
  }
  
  if (strcmp(topic, "/hello") == 0) {
    if (msg == "on") {
      digitalWrite(6, HIGH);
      Serial.println("on");
    } else if (msg == "off") {
      digitalWrite(6, LOW);
      Serial.println("on");
    }
  }
}
