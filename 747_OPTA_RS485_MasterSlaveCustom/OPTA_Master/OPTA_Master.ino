#include <ArduinoRS485.h>

int stato = 0;
unsigned long t1;
uint8_t dati[4];

void setup() {
  Serial.begin(115200); 
  while (!Serial);

  RS485.begin(4800);
  dati[2] = 0;
}

void loop() {
  switch (stato) {
    case 0:
      delay(1000);
      Serial.println("Invio comando");
      RS485.beginTransmission();
      dati[0] = 10;
      dati[1] = 1;
      dati[2] = !dati[2];
      dati[3] = 0;
      RS485.write(dati, sizeof(dati)); //ADDR      
      RS485.endTransmission();
      stato = 1;
      Serial.println("Attendo...");
      t1 = millis();
    break;

    case 1:  
      RS485.receive();
      auto aval = RS485.available();
      if (aval > 0) {
        int ret = RS485.read();

        Serial.print("RX: ");
        Serial.println(ret);

        if (ret == 1) {
          stato = 0;
          Serial.println("Passo a invio");
        }
      }

      if ((millis() - t1) > 10000) {
        stato = 0;
        Serial.println("TOUT: passo a invio");
      }    
      RS485.noReceive();
    break;
  }
}
