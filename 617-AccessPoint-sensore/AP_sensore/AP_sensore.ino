/**
 * Accessp Point con sensore e pagina con reload
 * */

#include <SPI.h>
#include <WiFiNINA.h>

//rete da creare e pass
char ssid[] = "ARDUINOWIFI";
char pass[] = "12345678"; //almeno 8 caratteri

int status = WL_IDLE_STATUS;
WiFiServer server(80);

//lo uso nel loop e in setup
IPAddress ip;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Arduino AP");


  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Errore HW");
    while (true);
  }

  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }

  // wait 10 seconds for connection:
  delay(5000);

  // start the web server on port 80
  server.begin();

  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      delayMicroseconds(10); // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            int val = map(analogRead(A0), 0, 1024, 0, 100);
            client.print("<html><head>");
            client.print("<meta http-equiv='refresh' content='1'>");
            client.print("<style>");
            client.print("#pbar { background-color: black; padding: 3px; width: 300px; }\n");
            client.print("#pbar>div { background-color: orange; height: 20px; width: ");
            client.print(val);
            client.print("%; }\n");

            client.print("</style></head><body><H1>Lettura sensore</H1>");
            
            client.print("Ingresso A0: ");
            client.print(val);
            client.print("<br/><div id='pbar'><div></div></div>");
            
            client.print("</body></html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        //if (currentLine.endsWith("GET /led")) {}
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
