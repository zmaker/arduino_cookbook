#include <SoftwareSerial.h>

/**
 *  Modbus slave example 1:
 *  The purpose of this example is to link a data array
 *  from the Arduino to an external device.
 *
 *  Recommended Modbus Master: QModbus
 *  http://qmodbus.sourceforge.net/
 */

#include <ModbusRtu.h>

SoftwareSerial RS485Serial(10, 11); // RX, TX

// data array for modbus network sharing
uint16_t au16data[16];

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  port : serial port
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus slave(1,RS485Serial,2); // this is slave @1 and RS-232 or USB-FTDI

void setup() {
  RS485Serial.begin(9600);  
  //Serial.begin( 9600 ); // baud-rate at 19200
  
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  slave.start();
}

void loop() {
  slave.poll( au16data, 16 );
  digitalWrite( 12, bitRead( au16data[1], 0 ));
}
