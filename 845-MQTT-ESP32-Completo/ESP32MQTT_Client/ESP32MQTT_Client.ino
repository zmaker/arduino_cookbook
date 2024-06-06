#include "parameters.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

const char* host = BOARD_NAME;
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
//prototipo della funzione richiamata alla ricezione di dati MQTT
void callback(char* topic, byte* payload, unsigned int length);
//prototipo funzione gestione connessione al server MQTT
void mqtt_reconnect();

void setup() {
  pinMode(SIGNAL_LED, OUTPUT);

  #if DEBUG > 0
  Serial.begin(115200);
  while (!Serial){
    delay(300);
    digitalWrite(SIGNAL_LED, !digitalRead(SIGNAL_LED));
    if (millis() > 5000) break;
  }
  Serial.println("Client ESP32 MQTT");
  #endif
  digitalWrite(SIGNAL_LED, LOW);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(SIGNAL_LED, !digitalRead(SIGNAL_LED));
    delay(100);
    count++;
    if (count > 500) {
      digitalWrite(SIGNAL_LED, HIGH);
      delay(3000);
      ESP.restart();
    }
  }
  digitalWrite(SIGNAL_LED, LOW);

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(BROKER_ADDRESS, BROKER_PORT);
  client.setCallback(callback);
  if (client.connect(BOARD_NAME)) {
    client.subscribe(TOPIC_SUB);
  }
}

void loop() {
  ArduinoOTA.handle();

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  if (!client.connected()){
    mqtt_reconnect();
  }
  client.loop();

  static unsigned long t1;
  static int count = 0;
  if ( (millis()-t1) > 3000) {
    digitalWrite(SIGNAL_LED, !digitalRead(SIGNAL_LED));

    if (client.connected()){
      Serial.println("TX msg");
      char msg[50];
    /*{
      "device":"myesp32", 
      "tipo":"temp", 
      "valore":12
    }
    */

      sprintf(msg, "{\"device\":\"myesp\",\"tipo\":\"hum\",\"valore\":\"%d\"}", count);
      client.publish(TOPIC_PUB, msg);
      count++;
    }

    t1 = millis();
  }

}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++ ){
    Serial.print((char)payload[i]);
  }
  Serial.println("");
}

void mqtt_reconnect(){
  while (!client.connected()) {
    if (client.connect(BOARD_NAME)) {
      client.subscribe(TOPIC_SUB);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}