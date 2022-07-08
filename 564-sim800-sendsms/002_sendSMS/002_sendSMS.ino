#include <SoftwareSerial.h>

#define CTRL_Z 26

SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup() {
  pinMode(4, INPUT);
  Serial.begin(9600);  
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
}

int bt, prevbt;

void loop() {
  bt = digitalRead(4);

  //FDD
  if (prevbt && !bt) {
    Serial.println("SMS..."); 
    String cmd = "AT+CMGS=\"+39numeroditel\"";
    //Serial.println(cmd);
    mySerial.println(cmd);
    updateSerial();
    mySerial.print("Hello zeppelinmaker");
    updateSerial();
    mySerial.write(26);     
    Serial.println("SMS inviato"); 
  }

  prevbt = bt;
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
