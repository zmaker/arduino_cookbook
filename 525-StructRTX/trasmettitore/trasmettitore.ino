#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

struct mydata {
  char cmd;
  int count;
  float temp;
  char str[20];
};

mydata dato = {'x', 0, 18.0f, "hello world!"};

void setup() {
  mySerial.begin(9600);

}

void loop() {
  
  mySerial.write((const uint8_t *)&dato, sizeof(struct mydata));
  mySerial.write((byte)'\n');
  
  dato.count++;
  delay(1000);
}
