#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(2);
DallasTemperature temp(&oneWire);

float tc = 0;
float tf = 0;

int nsonde = 0;

void setup(void) {
  Serial.begin(9600);
  temp.begin();
  nsonde = temp.getDeviceCount();
  Serial.print("sonde: ");
  Serial.println(nsonde);
}

void loop(void) { 
  
  temp.requestTemperatures(); 
  for (int i = 0; i < nsonde; i++) {
    Serial.print("sonda: ");
    Serial.println(i);
    tc = temp.getTempCByIndex(i);
    tf = temp.toFahrenheit(tc);
    Serial.print(" C  ");
    Serial.print(tc);
    Serial.print(" F  ");
    Serial.println(tf);    
  }
  delay(1000);
}
