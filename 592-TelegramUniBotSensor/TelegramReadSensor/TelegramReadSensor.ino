/**
 Per compilarla usare l'ultima versione di arduinojson 
 */
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "www.reelco.it";
char pass[] = "cardu450IX"; 
int status = WL_IDLE_STATUS;
WiFiSSLClient client;

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
const char* BotToken = "1900613751:AAFCSiTeF59uEZfPnf0JJn8HO1dIy0F4C_Y";    // your Bot Teken  
UniversalTelegramBot bot(BotToken, client);

const int ledPin = 2; 

void handleNewMessages(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++){
    String text = bot.messages[i].text;
    String chat_id = bot.messages[i].chat_id;
    if (text == "/sens"){
      int val = analogRead(A0);
      String msg = String(val);
      bot.sendMessage(chat_id, msg, "");
    } 
  }
}


void setup() {  
  pinMode(ledPin, OUTPUT);
  
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
 
  Serial.println("bot started");
}

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
unsigned long t1; // last time messages' scan has been done

void loop() {
 if (millis() - t1 > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    t1 = millis();
  }
}
