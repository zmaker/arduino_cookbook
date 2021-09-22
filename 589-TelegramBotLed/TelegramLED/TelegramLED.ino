#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "www.reelco.it";
char pass[] = "cardu450IX"; 
int status = WL_IDLE_STATUS;
WiFiSSLClient client;

#include <TelegramBot.h>  
const char* BotToken = "1900613751:AAFCSiTeF59uEZfPnf0JJn8HO1dIy0F4C_Y";    // your Bot Teken  
TelegramBot bot(BotToken,client);  

const int ledPin = 2; 

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
  bot.begin();
  Serial.println("bot started");
}

void loop() {
  message m = bot.getUpdates(); // Read new messages  
  if ( m.chat_id != 0 ){ //se ci sono aggiornamenti
      Serial.println(m.text);
      String msg = String(m.text);
      if (msg == "On") {
        digitalWrite(ledPin, HIGH);  
        Serial.println("led on");  
        //bot.sendMessage(m.chat_id, "The Led is now ON");
      } else if (msg == "Off") {
        digitalWrite(ledPin, LOW);  
        Serial.println("led off");  
        //bot.sendMessage(m.chat_id, "The Led is now OFF");
      }
      //bot.sendMessage(m.chat_id, "ok\n");
   } 
   delay(500);
}
