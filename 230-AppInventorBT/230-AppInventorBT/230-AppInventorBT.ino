#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7); //6 RX e 7 TX

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(9600);

  pinMode(13, OUTPUT);
}

String line = "";
void loop() {  
  if (SSerial.available()){
    char ch = SSerial.read();        
    if ((ch == '\n') || (ch == '\r')){
      process(line);
      
      line = ""; // Clear recieved buffer      
    } else {
      line += ch;  
    }
  }
}

void process(String line) {
  Serial.print("Arduino Received: ");
  Serial.println("#"+line+"#");
  Serial.println(line.length());
      
  if (line.equals("on")) {
      digitalWrite(13, HIGH);
      Serial.println("ON");
    }
    if (line.equals("off")) {
      digitalWrite(13, LOW);
      Serial.println("OFF");
    }
}
