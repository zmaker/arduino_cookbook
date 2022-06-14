#include <SPI.h>
#include <WiFiNINA.h>

char ssid[20] = "arduinonet"; 
char pass[20] = "123Stella!";

//valori da impostare
String wifi_ssid;
String wifi_pass;

int status;
WiFiServer server(80);
WiFiClient client;

enum stati {apconfig, connection, working, quit, park} stato;

void setup() {
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  int tentativi = 0;
  while ((!Serial) && (tentativi < 10)) {
    delay(500);
    digitalWrite(13, !digitalRead(13));
    //tentativi++;
  }
  digitalWrite(13, HIGH);
  Serial.println("Access Point Configuration");
  
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");    
    while (true);
  }

  WiFi.config(IPAddress(192, 168, 4, 1));
  
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");    
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();
  Serial.println("Server pronto");
}


void loop() {
  switch (stato){
    case apconfig:
      //attiva un access point per impostare la rete a cui collegarsi
      act_apconfig();
      break;
    case connection:
      //si collega alla rete indicata
      act_connection();
      break;      
    case working:
      //chiama il servizio
      act_working();
      break;
    case quit:
      //termina 
      act_quit();
      break;
    case park:      
      break;
  }
  /*
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
      Serial.print("Indirizzo server: 192.168.4.1");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
  */  
}

void act_apconfig(){
  //presenta una pagina con form per specificare le credenziali di rete
  client = server.available(); 

  if (client) {                               
    String line = "";         
    String page = "";
    String data = "";
    while (client.connected()) {           
      if (client.available()) { 
        char c = client.read(); 
        Serial.write(c);  
              
        if (c == '\n'){          
          if (line.indexOf("GET ") >= 0) {            
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
        } else if (c != '\r'){
          line += c;
        }
        
      }
    }    
    client.stop();    
  }
}

void act_connection(){
  Serial.println("Server stop");
  //server.stop();
  Serial.println("WiFi disconnect");
  WiFi.disconnect();
  delay(5000);
  Serial.println("shutdown modulo");
  WiFi.end();
  delay(5000);
  Serial.println("Restarting...");

  status = WL_IDLE_STATUS;

  wifi_ssid.toCharArray(ssid, wifi_ssid.length()+1);
  wifi_pass.toCharArray(pass, wifi_pass.length()+1);

  Serial.print("Mi collego al Wifi... ");Serial.println(ssid);
  Serial.print("pass:");Serial.println(pass);
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
    Serial.println("Collegato al server web");
    String req = "GET /helloworld.txt HTTP/1.1";
    client.println(req);
    client.println("Host: www.zeppelinmaker.it");
    client.println("Connection: close");
    client.println();
  }

  while(true) {
    while (client.available()) {
      char c = client.read();
      Serial.write(c);  
    }

    if (!client.connected()) {
      Serial.println("\n\nScollegato dal server web");
      client.stop();
      stato = quit;
      break;      
    }
  }
}

void act_quit() {
  Serial.println("disconnect wifi");
  WiFi.disconnect();
  Serial.println("shutdown modulo");
  WiFi.end();
  Serial.println("END");
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
  
  String p1 = data.substring(0, data.indexOf("&"));
  String p2 = data.substring(data.indexOf("&")+1);
  wifi_ssid = p1.substring(p1.indexOf("=")+1);
  wifi_pass = p2.substring(p2.indexOf("=")+1);

}
