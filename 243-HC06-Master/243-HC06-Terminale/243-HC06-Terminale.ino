/*
 * https://www.instructables.com/id/How-to-Configure-HC-05-Bluetooth-Module-As-Master-/
The required AT commands to set the configuration as master

    AT+RMAAD (To clear any paired devices)
    AT+ROLE=1 (To set it as master)
    AT+CMODE=0 (To connect the module to the specified Bluetooth address and this Bluetooth address can be specified by the binding command)
    AT+BIND=xxxx,xx,xxxxxx (Now, type AT+BIND=98d3,34,906554 obviously with your respective address to the slave. Note the commas instead of colons given by the slave module.
    AT+UART=38400,0,0 (To fix the baud rate at 3840
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
