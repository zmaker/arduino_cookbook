#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiServer server(80);

int status = WL_IDLE_STATUS;

enum httpmet {GET, POST} method;

void setup() {
  pinMode(6, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
     delay(1);  
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi KO! STOP!");
    while(true);  
  }

  Serial.println("Mi collego al Wifi...");
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.print("\nCollegato");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");Serial.println(ip);
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String line = "";
    String page = "";
    String data = "";
    int byte_to_read;
    while(client.connected()) {
      if (client.available()) {        
        char c = client.read();
        Serial.write(c);
        if (c == '\n'){          

          //Serial.print("> ");Serial.println(line);
          if (line.indexOf("GET ") >= 0) { 
            method = GET;
                       
            page = line.substring(line.indexOf("/"), line.indexOf(" HTTP/1.1"));
            Serial.print("REQ page: ");Serial.print(page);Serial.println("#");

            if (page.indexOf("?") >= 0) {
              data = page.substring(page.indexOf("?")+1);
              Serial.print("dati in GET: ");Serial.print(data);Serial.println("#");
              page = page.substring(0, page.indexOf("?"));
            }
            
          } else if (line.indexOf("POST ") >= 0) { 
            method = POST;

            page = line.substring(line.indexOf("/"), line.indexOf(" HTTP/1.1"));
            Serial.print("POST page: ");Serial.print(page);Serial.println("#");
          } 

           
          if ((method == GET) && (line.length() == 0)) {            
            if (page == "/") {
              response_index(&client);            
            } else {
              response_notfound(&client);
            }
            break;
          }

          if (method == POST) {            
            if (line.indexOf("Content-Length: ") >= 0) {
              String str = line.substring(line.indexOf(":")+1);
              byte_to_read = str.toInt();              
              Serial.print("byte to read: ");Serial.println(byte_to_read);             
            }

            if (line.length() == 0) {
              for (int i = 0; i < byte_to_read; i++) {
                data += (char)client.read(); 
              }
              Serial.print("payload: ");Serial.println(data); 

              response_page(&client, data);
              break;
            }              
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

void response_index(WiFiClient *client){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY>");
  client->println("<FORM action='/savedata' method='POST'>");
  client->println("<INPUT type='text' name='val'></INPUT>");   
  client->println("<INPUT type='submit'></INPUT>");   
  client->println("</FORM>");   
  client->println("</BODY>"); 
  client->println("</HTML>"); 
}

void response_page(WiFiClient *client, String data){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>Dati ricevuti in post</h1>");  
  client->println(data); 
  client->println("<br/><a href='/'>INDEX</a>"); 
  client->println("</BODY>"); 
  client->println("</HTML>"); 

  //val=123
  String str = data.substring(data.indexOf("=")+1);
  int pwm = constrain(str.toInt(), 0, 255);
  analogWrite(6, pwm);
}

void response_notfound(WiFiClient *client){
  client->println("HTTP/1.1 404 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>ERROR 404</h1></BODY>"); 
  client->println("</HTML>"); 
}
