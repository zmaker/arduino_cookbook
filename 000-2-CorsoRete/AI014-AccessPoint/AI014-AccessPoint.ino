#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "arduino.wifi";
char pass[] = "arduino123";  //almeno 8 caratteri!!!

int status;
WiFiServer server(80);

void setup() {  
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  int t = 0;
  while ((!Serial) && (t < 10)) {
     delay(500);   
     digitalWrite(13, !digitalRead(13));
     t++;
  }
  digitalWrite(13, HIGH);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi KO! STOP!");
    while(true);  
  }

  /*
    WiFi.config(ip);
    WiFi.config(ip, dns);
    WiFi.config(ip, dns, gateway);
    WiFi.config(ip, dns, gateway, subnet);
   */
  WiFi.config(IPAddress(192,168,4,1));
  Serial.print("Creazione access Point: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creazione access Point fallita ");
    while(true);
  }
  delay(10000);

  server.begin();
}

void loop() {
  if (status != WiFi.status()) {
    status = WiFi.status();
    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connesso");      
    } else {
      Serial.println("Device disconnesso");      
    }
  }

  WiFiClient client = server.available();
  if (client) {
    String line = "";
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);  
        
        if (c == '\n'){
          Serial.println(line);
          if (line.length() == 0) {
            Serial.println("\nRESP\n");
            response(&client);
            break;
          }
          
          line = "";
        } else if (c != '\r'){
          line += c;
        }
        
      }
    }
    delay(1);
    client.stop();  
  }
  
}

void response(WiFiClient *client){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>hello from iot 33 AP</h1></BODY>"); 
  client->println("</HTML>"); 
}
