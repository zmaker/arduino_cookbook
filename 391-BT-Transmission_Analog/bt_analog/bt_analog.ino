#include <SoftwareSerial.h>
SoftwareSerial SSerial(7, 8);

void setup() {
  Serial.begin(9600);
  Serial.println("ok");
  SSerial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

String str = "";
unsigned long t1;

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

  if ( digitalRead(2) ) {
    SSerial.println("bton");
    delay(300);
  }
  if ( digitalRead(3) ) {
    SSerial.println("btoff");
    delay(300);
  }

  if ((millis() - t1) > 300) {
    String sensor = String(analogRead(A0));
    SSerial.println(sensor);
    t1 = millis();  
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
  } else if (c == 'p') {
    String n = str.substring(2);
    int pwm = (int)n.toInt();
    Serial.print("PWM=");
    Serial.println(pwm);
    analogWrite(6, pwm);
  }
}




  
