/*
https://www.grc.com/fingerprints.htm
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "nomewifi"
#define STAPSK  "passwordwifi"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "maker.ifttt.com";
const int httpsPort = 443;

const char fingerprint[] PROGMEM = "AA 75 CB 41 2E D5 F9 97 FF 5D A0 8B 7D AC 12 21 08 4B 00 8C";

void setup() {
  pinMode(5, INPUT);
  pinMode(16, OUTPUT);
  
  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
}

void loop() {
  digitalWrite(16, LOW);
  if (digitalRead(5)) {
    digitalWrite(16, HIGH);
    ifttt();  
  }
}


void ifttt() {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/trigger/buttonpressed/with/key/rnTBlbxerrp71dz-QkHkarKUPAAD_qHjtwdJwuuMfB";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection"); 
}
