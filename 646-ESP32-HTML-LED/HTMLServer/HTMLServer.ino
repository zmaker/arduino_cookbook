#include <WiFi.h>
#include <ESPmDNS.h>

const char* ssid = "wifiname";
const char* password = "password";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //così posso trovare la scheda anche all'indirizzo
  // http://esp32.local/
  if (MDNS.begin("esp32")) {
    Serial.println("Abilito: http://esp32.local/");
  }
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {    
    String header;
    String currentLine = ""; 
    while (client.connected()) {
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c); 
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /2/on") >= 0) {
              digitalWrite(2, HIGH);
            }
            if (header.indexOf("GET /2/off") >= 0) {
              digitalWrite(2, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<body><h1>ESP32</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            if (digitalRead(2)) {
              client.println("<p><a href=\"/2/off\"><button>OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/on\"><button>ON</button></a></p>");
            } 
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
            
            
          } else {
            currentLine = "";  
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }  
    client.stop();
    Serial.println("Client disconnected.");    
  }
}
