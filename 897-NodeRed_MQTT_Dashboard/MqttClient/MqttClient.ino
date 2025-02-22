#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "nomerete";
const char* password = "***********";

//https://www.hivemq.com/mqtt/public-mqtt-broker/
const char* mqttBroker = "broker.hivemq.com";
const int mqttPort = 1883;

const char* temperatureTopic = "client/sensor/temp";
const char* humidityTopic = "client/sensor/hum";
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

int temp = 20;
int hum = 50;

unsigned long t1 = 0;

//prototipi
void callback(char *topic, byte *payload, unsigned int len);
void mqtt_reconnect();
void pubMsg(const char* topic, int val);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("!");
  Serial.println("Connesso");

  mqttClient.setServer(mqttBroker, mqttPort);
  mqttClient.setCallback(callback);

  randomSeed(analogRead(1));
}

void loop() {
  if (!mqttClient.connected()) {
    mqtt_reconnect();
  }

  if ((millis() - t1) > 5000) {

    hum += random(-3, 3);
    temp += random(-3, 3); 

    pubMsg(temperatureTopic, temp);
    pubMsg(humidityTopic, hum);

    t1 = millis();
  }
}

void callback(char *topic, byte *payload, unsigned int len) {
  Serial.print("MSG RX: ");
  Serial.println(topic);
}

void mqtt_reconnect(){
  while (!mqttClient.connected()) {
    Serial.println("Reconnect MQTT server...");
    String clientid = "myLolin32-" + String(random(20000));

    Serial.println(clientid);
    if (mqttClient.connect(clientid.c_str())) {
      Serial.println("Connected");
    } else {
      Serial.println("not connected");
      delay(5000);
    }
  }
}

void pubMsg(const char* topic, int val){
  char msg[5];
  snprintf(msg, 5, "%d", val);
  Serial.println(msg);

  mqttClient.publish(topic, msg);
  Serial.print(topic);
  Serial.print(":");
  Serial.println(val);
}