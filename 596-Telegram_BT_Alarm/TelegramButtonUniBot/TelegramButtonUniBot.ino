/**
 Per compilarla usare l'ultima versione di arduinojson 
 */
#include <SPI.h>
#include <WiFiNINA.h>

#include "secrets.h"

int status = WL_IDLE_STATUS;
WiFiSSLClient client;

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
UniversalTelegramBot bot(token, client);
String chat_id;
boolean has_cid = false;

void setup() {  
  pinMode(2, OUTPUT); //led servizio
  pinMode(4, OUTPUT); //reset
  pinMode(3, INPUT); //lettura tasto su flipflop
  
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
  //controllo messaggi
  if ((millis() - t1) > 1000) {        
    t1 = millis();  

    //verifica telegram
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("ci sono messaggi");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
  }

  //verifica pulsante
  if (digitalRead(3)) { //il pulsante è stato premuto
    pulse(4); //azzero il FF
    if (has_cid) {
      bot.sendMessage(chat_id, "BT premuto", "");       
    }
  }
}

void handleNewMessages(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++){
    String text = bot.messages[i].text;
    if (text == "/monitor") {
      has_cid = true;  
      chat_id = bot.messages[i].chat_id;
      Serial.println(chat_id);
    }
  }
}

void pulse(int pin) {
  digitalWrite(pin, HIGH);
  delay(10);  
  digitalWrite(pin, LOW);
}
