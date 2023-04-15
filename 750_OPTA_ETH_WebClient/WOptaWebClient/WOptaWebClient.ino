#include <PortentaEthernet.h>
#include <Ethernet.h>
#include <SPI.h>

char server[] = "www.zeppelinmaker.it";
char page[] = "/helloworld.txt";

EthernetClient client;

int stato = 0;
unsigned long t1 = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("ETH Client");

  pinMode(LED_D0, OUTPUT);
  pinMode(LED_D3, OUTPUT);
  pinMode(BTN_USER, INPUT);

  if (!Ethernet.begin()) {
    Serial.println("ETH ERROR");
    while(true) {
      digitalWrite(LED_D3, !digitalRead(LED_D3));
      delay(100);
    }
  } else {
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
}

void loop() {
  switch(stato) {
    case 0:
      if (client.connect(server, 80)) {
        Serial.print("IP SRV: ");
        Serial.println(client.remoteIP());
        client.println("GET "+String(page) + " HTTP/1.1");
        client.println("Host: "+String(server) );
        client.println("Connection: close");
        client.println();
        stato = 1;
      } else {
        Serial.println("errore connessione");
        stato = 2;
      }
      break;
    case 1:
      while(client.available()) {
        char c = client.read();
        Serial.write(c);
      }
      if (!client.connected()) {
        client.stop();
        t1 = millis();
        stato = 2;
      }
      break;
    case 2:
      if ((millis() - t1) > 1000){
        digitalWrite(LED_D0, !digitalRead(LED_D0));
        t1 = millis();
      }

      if (!digitalRead(BTN_USER)) {
        digitalWrite(LED_D0, LOW);
        stato = 0;
      }

      break;
  }

}
