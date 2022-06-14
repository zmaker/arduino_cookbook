/*
Leggo una pagina
e accendo un led a seconda del contenuto
Il led è sul pin 2
*/
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;           

int status = WL_IDLE_STATUS;
char server[] = "www.zeppelinmaker.it"; 
String page = "/corsoarduino/led.php";

WiFiClient client;

enum stati {connectwifi, request, response, disconnetti} stato;

void setup() {
  pinMode(2, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("no module");
    while (true);
  }

}

void loop() {
  switch (stato) {
    case connectwifi:
      act_connectwifi();
    break;
    case request:
      act_request();
    break;
    case response:
      act_response();
    break;
    case disconnetti:
      act_disconnetti();
    break;
  }
}

void act_connectwifi(){
  while (status != WL_CONNECTED) {
    Serial.print(".");
    status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.println("\nConnesso");
  stato = request;
}

void act_request(){
  Serial.println("request...");
  if (client.connect(server, 80)) {   
    // Make a HTTP request:
    client.println("GET "+String(page)+" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
    stato = response;
  } else {
    Serial.println("connessione al server rifiutata");
    stato = disconnetti;
  }
}

String line = "";

void act_response(){    
  while (client.available()) {
    char c = client.read();
    if (c == '\n') {
      //Serial.print(">");Serial.println(line);                

      if (line.indexOf("led=on") >= 0) {
        digitalWrite(2, HIGH);  
        Serial.println("ON");
      } else if (line.indexOf("led=off") >= 0) {
        digitalWrite(2, LOW);
        Serial.println("OFF");
      }
      
      line = "";
    } else if (c != '\r') {
      line += c;
    }      
  }
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();     
    delay(5000);   
    stato = request;
  }
}

void act_disconnetti(){
  Serial.println("disconnesione dal wifi.");
  WiFi.disconnect();
  Serial.println("disconnesso.");
  while(true);
}
