#include <SPI.h>
#include <WiFiNINA.h>

int status;
WiFiServer server(80);
WiFiClient client;

char ssid[20] = "arduinonet"; 
char pass[20] = "123stella"; 
String wifi_ssid;
String wifi_pass;

enum stati {apconfig, connection, working, quit, park} stato;

void setup() {
  Serial.begin(9600);
  while (!Serial){
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi ko");
    while(true);  
  }

  WiFi.config(IPAddress(192,168,4,1));
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("AP ko");
    while(true);  
  }
  Serial.println("AP pronto");
  delay(10000);
  server.begin();
  Serial.println("Server pronto (192.168.4.1)");
}

void loop() {
  switch (stato) {
    case apconfig:
      act_apconfig();
      break;
    case connection:
      act_connection();
      break;
    case working:
      act_working();
      break;
    case quit:
      act_quit();
      break;
    case park:
      
      break;
  }
}

void act_apconfig(){
  client = server.available();
  if (client) {
    String line = "";
    String page = "";
    String data = "";
    while (client.connected()) {
      char c = client.read();
      Serial.write(c);
      if (c == '\n') {
        if (line.indexOf("GET ") >= 0) {
          //GET /form.html?p1=val HTTP/1.1
          page = line.substring(line.indexOf("/"), line.indexOf(" HTTP/1.1"));

          if (page.indexOf("?") >= 0) {
            data = page.substring(page.indexOf("?")+1);
            page = page.substring(0, page.indexOf("?"));
          }
        }

        if (line.length() == 0) {
          if (page == "/") {
            response_index(&client);
          } else if (page == "/savedata") {
            response_savedata(&client, data);
            stato = connection;
          } 
          break;
        }
        
        line = "";        
      } else if (c != '\r') {
        line += c;  
      }
    }  
  } 
  client.stop();
}
void act_connection(){
  WiFi.disconnect();
  delay(5000);
  WiFi.end();
  delay(5000);
  Serial.println("Restart");
  wifi_ssid.toCharArray(ssid, wifi_ssid.length()+1);
  wifi_pass.toCharArray(pass, wifi_pass.length()+1);
  status = WL_IDLE_STATUS;  

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.print("\n");
  Serial.println("Collegato");

  stato = working;
}

void act_working(){
  if (client.connect("www.zeppelinmaker.it", 80)) {
    client.println("GET /helloworld.txt HTTP/1.1");
    client.println("Host: www.zeppelinmaker.it");
    client.println("Connection: close");
    client.println();
  }

  while (true){
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
    if (!client.connected()) {
      client.stop();
      stato = quit;
      break;
    }
  }
}
void act_quit(){
   WiFi.disconnect();
  delay(5000);
  WiFi.end();
  delay(5000);
  stato = park;
}

void response_index(WiFiClient *client){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>Dati Wifi</h1>");
  client->println("<FORM action='/savedata'>");
  client->println("<input type='text' name='rete'/>");  
  client->println("<input type='password' name='pass'/>");
  client->println("<input type='submit'/>");
  client->println("</FORM></BODY>"); 
  client->println("</HTML>"); 
}

void response_savedata(WiFiClient *client, String data){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>Connessione...</h1>");     
  client->println("</BODY>"); 
  client->println("</HTML>"); 

  //?nome=asada&pass=sdsdsd&
  String p1 = data.substring(0, data.indexOf("&"));
  String p2 = data.substring(data.indexOf("&")+1);
  wifi_ssid = p1.substring(p1.indexOf("=")+1);
  wifi_pass = p2.substring(p2.indexOf("=")+1);
}
