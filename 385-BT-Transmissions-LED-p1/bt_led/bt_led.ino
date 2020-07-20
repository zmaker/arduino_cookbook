#include <SoftwareSerial.h>
SoftwareSerial SSerial(7, 8);

void setup() {
  Serial.begin(9600);
  Serial.println("ok");
  SSerial.begin(9600);

  pinMode(13, OUTPUT);
}

String str = "";

void loop() {
  if (SSerial.available()) {
    char ch = SSerial.read();
    Serial.println(ch);
    if ( (ch == '\n') || (ch == '\r') ) { 
      cmd(str);
      str = "";
    } else {
      str += ch;
    }
  }
}

void cmd(String str) {
  char c = str.charAt(0);
  if (c == 'a') {
    Serial.println("ON");
    digitalWrite(13, HIGH);  
  } else if (c == 's') {
    Serial.println("OFF");
    digitalWrite(13, LOW);  
  }
}




  
