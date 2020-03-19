//Testato con QModMaster
//https://github.com/yaacov/ArduinoModbusSlave

// https://en.wikipedia.org/wiki/Modbus

#include <ModbusSlave.h>
#include <SoftwareSerial.h>
SoftwareSerial RS485Serial(10, 11); // RX, TX

Modbus slave(RS485Serial, 1, 2);

void setup() {
    // RS485 control pin must be output
    pinMode(2, OUTPUT);

    //il led
    pinMode(12, OUTPUT);
    
    /* register handler functions.
     * into the modbus slave callback vector.
     */
    slave.cbVector[CB_WRITE_COILS] = writeDigitalOut;
    
    // set Serial and slave at baud 9600.
    Serial.begin( 9600 );
    RS485Serial.begin(9600);
    slave.begin( 9600 );
}

void loop() {
    /* listen for modbus commands con serial port.
     *
     * on a request, handle the request.
     * if the request has a user handler function registered in cbVector.
     * call the user handler function.
     */ 
    slave.poll();
}


/**
 * Handle Force Single Coil (FC=05) and Force Multiple Coils (FC=15)
 * set digital output pins (coils).
 * 
 * Dalla pagina di wikipedia addr: Coil  Read-write  1 bit   00001 - 09999 
 */
uint8_t writeDigitalOut(uint8_t fc, uint16_t address, uint16_t length) {
  Serial.print("FC=05: ");
  Serial.println(fc);
  Serial.println(address);
  Serial.println(length);

  if (address == 12) {
    digitalWrite(12, slave.readCoilFromBuffer(0));
  }

    return STATUS_OK;
}
