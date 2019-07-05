/*
 * https://www.adrirobot.it/Modulo_hc-05/modulo_hc-05.htm
https://www.lombardoandrea.com/arduino-hc-05-base/
https://www.instructables.com/id/How-to-Configure-HC-05-Bluetooth-Module-As-Master-/

The required AT commands to set the configuration as SLAVE

    AT+RMAAD (To clear any paired devices)
    AT+ROLE=0 (To set it as slave)
    AT+ADDR (To get the address of this HC-05, remember to jot the address down as it will be used during master configuration)
    AT+UART=38400,0,0 (To fix the baud rate at 38400)
    
*/



#include <SoftwareSerial.h>

SoftwareSerial BTserial(6, 7); // RX | TX
// Connect the HC-08 TX to Arduino pin 2 RX.
// Connect the HC-08 RX to Arduino pin 3 TX through a voltage divider.

#define __BAUD 38400

void setup(){
  Serial.begin(__BAUD);
  BTserial.begin(__BAUD);
  delay(1000);
  Serial.println("ready...");
}

void loop() {  
  if (BTserial.available()) {
    Serial.write(BTserial.read());
  }
  if (Serial.available()) {
    BTserial.write(Serial.read());
  }
}
