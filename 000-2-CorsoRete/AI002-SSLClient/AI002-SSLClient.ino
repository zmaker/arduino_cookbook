/*
This example creates a client object that connects and transfers
data using always SSL.

Per poter accedere alla pagine si deve usare il tool per scaricare il certificato dal server
e quindi aggiungerlo alla scheda.
bisogna aggiungere il dominio www.zeppelinamker.it

*/

#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;           

int status = WL_IDLE_STATUS;
char server[] = "www.zeppelinmaker.it"; 
String page = "/helloworld.txt";

WiFiSSLClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.println("Connected to WiFi");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET "+page+" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
  }

  while (true) {
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();     
      break;   
    }
  }

  Serial.println("disconnecting from wifi.");
  WiFi.disconnect();

  Serial.println("off wifi.");
  WiFi.end();
}

void loop() {
  
}
