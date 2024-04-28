#include <SHT1x-ESP.h>

//per micro a 5V
SHT1x sht1x(10, 11);
//per micor a 3V3
//SHT1x sht1x(10, 11, SHT1x::Voltage::DC_3_3v);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Serial.println("SHT10");
}

void loop() {
  float t, h;
  t = sht1x.readTemperatureC();  
  h = sht1x.readHumidity();

  /*
  Serial.print("t: ");
  Serial.print(t);
  Serial.print("\th: ");
  Serial.println(h);
  delay(1000);
  */
  Serial.print(t);
  Serial.print(", ");
  Serial.println(h);
  delay(200);
}


