#include <ModbusMaster.h>

#include <SoftwareSerial.h>
SoftwareSerial RS485Serial(10, 11); // RX, TX

/*!
  We're using a MAX485-compatible RS485 Transceiver.
  Rx/Tx is hooked up to the hardware serial port at 'Serial'.
  The Data Enable and Receiver Enable pins are hooked up as follows:
*/
#define MAX485_DE      2
#define MAX485_RE     3

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_DE, 1);
  digitalWrite(MAX485_RE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_DE, 0);
  digitalWrite(MAX485_RE, 0);
}

void setup()
{
  pinMode(MAX485_DE, OUTPUT);
  pinMode(MAX485_RE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_DE, 0);
  digitalWrite(MAX485_RE, 0);
  

  // Modbus communication runs at 115200 baud
  Serial.begin(9600);
  RS485Serial.begin(9600);

  // Modbus slave ID 1
  node.begin(1, RS485Serial);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

int led = LOW;

void loop() {
  //imposta il led
  result = node.writeSingleCoil(0x000C, led);
  led = !led;
  
  delay(1000);
}
