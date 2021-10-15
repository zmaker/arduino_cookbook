#include "secrets.h"

#include <SPI.h>
#include <WiFiNINA.h>

int status = WL_IDLE_STATUS;
WiFiSSLClient client;

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
UniversalTelegramBot bot(token, client);

void setup() {  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!\nSTOPPED");    
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);    
    status = WiFi.begin(ssid, pass);
    delay(2000);
  }
  Serial.println("Connected to wifi");
}

unsigned long t1; 

void loop() {
 if ((millis() - t1) > 1000) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("ci sono messaggi");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    t1 = millis();
  }
}

void handleNewMessages(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++){
    String text = bot.messages[i].text;
    String chat_id = bot.messages[i].chat_id;
    if (text == "/red") {
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      bot.sendMessage(chat_id, "OK", "");
    } else if (text == "/yellow") {
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      bot.sendMessage(chat_id, "OK", "");
    } else if (text == "/green") {
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      bot.sendMessage(chat_id, "OK", "");
    }
  }
}
