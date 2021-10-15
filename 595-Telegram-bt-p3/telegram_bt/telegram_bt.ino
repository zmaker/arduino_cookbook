#include "secret.h"
#include <SPI.h>
#include <WiFiNINA.h>

int status = WL_IDLE_STATUS;
WiFiSSLClient client;

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
UniversalTelegramBot bot(token, client);

void setup() {
  pinMode(2, OUTPUT); //led
  pinMode(4, OUTPUT); //reset ff
  pinMode(3, INPUT); //lettura pulsante
  
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
  if (digitalRead(3)) {
    digitalWrite(2, HIGH);  
  }
  
  if ((millis()-t1) >= 1000) {
    t1 = millis();

    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("ci sono messaggi");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
  }
}

void handleNewMessages(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++){
    String text = bot.messages[i].text;
    String chat_id = bot.messages[i].chat_id;

    if (text == "/bt") {
      if (digitalRead(2)) {
        digitalWrite(2, LOW);
        pulse(4);
        bot.sendMessage(chat_id, "BT premuto", "");  
      } else {
        bot.sendMessage(chat_id, "BT non premuto", "");  
      }
    }
  }
}

void pulse (int pin) {
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}
