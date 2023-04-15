#include <SPI.h>
#include <PortentaEthernet.h>
#include <Ethernet.h>

IPAddress ip(192, 168, 1, 100);
EthernetServer server(80);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("web server opta");

  pinMode(LED_D3, OUTPUT);

  Ethernet.begin(ip);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("web server opta");
    while (true){
      digitalWrite(LED_D3, !digitalRead(LED_D3));
      delay(100);
    }
  }

  server.begin();
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    boolean endline;
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if ((c == '\n') && endline) {
          client.println("HTTP/1.1 200 OK");
          client.println("ContentType: text/html");
          client.println("Connection: close");
          client.println("Refresh: 3");
          client.println();
          client.println("<html>");
          int v = analogRead(A7);
          client.println("<h1>I8: ");
          client.println(v);
          client.println("</h1>");
          client.println("</html>");
          break;
        }

        if (c == '\n') {
          endline = true;
        } else if (c != '\r') {
          endline = false;
        }
      }
    }
    delay(1);
    client.stop();
  }

}
