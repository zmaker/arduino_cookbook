#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

struct mydata {
  char cmd;
  int count;
  float temp;
  char str[20];
};

mydata dato;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

byte buff[20];
int i = 0;

void loop() {  
  while (mySerial.available()) {
    byte n = mySerial.read();  
    if ((char)n == '\n') {

      //mySerial.write((const uint8_t *)&dato, sizeof(struct mydata));

      memcpy(&dato, buff, i);

      Serial.print(dato.cmd);Serial.print(" - ");
      Serial.print(dato.count);Serial.print(" - ");
      Serial.print(dato.temp);Serial.print("\n");
      Serial.print(dato.str);Serial.print("\n");
      
      Serial.print("ricevuti: ");  
      Serial.print(i);  
      Serial.println(" bytes - END");  
      i = 0;
    } else {
      buff[i] = n; 
      i++;
    }    
  }
  //mySerial.write((const uint8_t *)&dato, sizeof(struct mydata));
}
