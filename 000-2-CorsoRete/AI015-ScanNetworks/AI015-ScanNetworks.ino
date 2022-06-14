#include <SPI.h>
#include <WiFiNINA.h>

void setup() {
  Serial.begin(9600);
  
  while(!Serial) {
    delay(1);  
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while(1);  
  }

  byte mac[6];
  char str[4];
  WiFi.macAddress(mac);
  Serial.print("mac: ");  
  for (int i = 5; i >= 0; i--) {
   sprintf(str, "%02X", mac[i]);  
   Serial.print(str);
   if (i > 0) Serial.print(":");    
  }
  Serial.print("\n");  

}

void loop() {
  int n = WiFi.scanNetworks();
  if (n >= 0) {
    Serial.print("n. reti: "); Serial.println(n);
    for (int i = 0; i < n; i++) {
      Serial.print(WiFi.SSID(i));        
      Serial.print("\tSgn:");
      Serial.print(WiFi.RSSI(i));        
      Serial.print("dBm\t Enc: ");
      decodeEnc(WiFi.encryptionType(i));
    } 
  }
  delay(10000);
}

void decodeEnc(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      Serial.println("Unknown");
      break;
  }
}
