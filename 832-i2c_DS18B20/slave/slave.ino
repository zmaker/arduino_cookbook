#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(2);
DallasTemperature temp(&oneWire);

//indirizzo 123 decimale
#define I2C_ADDR 0x7B

uint8_t reg;

int nsonde;
unsigned long t1;

union databuff {
  float tc[5];
  uint8_t buff[20];
} dati;

//riceve i dati dal master
void riceviDati(int n) {  
  reg = (uint8_t)Wire.read();  
}

//invia i dati al master
void inviaDati() {    
  for (int i = 0 ; i < 20; i++){
    Wire.write((int)dati.buff[i]);
  }
}

void setup() {  
  Wire.begin(I2C_ADDR);  
  Wire.onReceive(riceviDati);  
  Wire.onRequest(inviaDati);
  Serial.begin(115200);
  delay(3000);
  Serial.println("slave");

  temp.begin();
  nsonde = temp.getDeviceCount();
  Serial.print("sonde: ");
  Serial.println(nsonde);
  temp.requestTemperatures();
}

void loop() {
  if ((millis() - t1) > 5000) {
    for (int i = 0; i < 2; i++) {
      if (i < nsonde) {
        Serial.print("sonda: ");
        Serial.print(i);
        dati.tc[i] = temp.getTempCByIndex(i);
        Serial.print(" C  ");
        Serial.println(dati.tc[i]);
      } else {
        dati.tc[i] = 0.0;
      }
    }
    temp.requestTemperatures();
    t1 = millis();
  }
}

