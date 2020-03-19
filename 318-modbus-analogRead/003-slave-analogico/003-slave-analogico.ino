//Testato con QModMaster
//https://github.com/yaacov/ArduinoModbusSlave

#include <ModbusSlave.h>
#include <SoftwareSerial.h>
SoftwareSerial RS485Serial(10, 11); // RX, TX

Modbus slave(RS485Serial, 1, 2);

void setup() {
    // RS485 control pin must be output
    pinMode(2, OUTPUT);

    pinMode(12, OUTPUT);  //LED
    pinMode(5, INPUT);    //Button
    
    /* register handler functions.
     * into the modbus slave callback vector.
     */
    slave.cbVector[CB_READ_COILS] = readDigital;
    slave.cbVector[CB_READ_DISCRETE_INPUTS] = readDigital;
    slave.cbVector[CB_WRITE_COILS] = writeDigitalOut;
    slave.cbVector[CB_READ_INPUT_REGISTERS] = readAnalogIn;
    
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
 * Handel Read Input Registers (FC=04)
 * write back the values from analog in pins (input registers).
 */
uint8_t readAnalogIn(uint8_t fc, uint16_t address, uint16_t length) {
  Serial.print("FC=04: ");
  Serial.println(fc);
  Serial.println(address);
  Serial.println(length);
    // read analog input
    for (int i = 0; i < length; i++) {
        // write uint16_t value to the response buffer.
        slave.writeRegisterToBuffer(i, analogRead(A0));
    }
    return STATUS_OK;
}


/**
 * Handle Read Input Status (FC=01/02)
 * write back the values from digital pins (input status).
 *
 * handler functions must return void and take:
 *      uint8_t  fc - function code.
 *      uint16_t address - first register/coil address.
 *      uint16_t length/status - length of data / coil status.
 */
uint8_t readDigital(uint8_t fc, uint16_t address, uint16_t length) {
    Serial.print("FC=01/02: ");
  Serial.println(fc);
  Serial.println(address);
  Serial.println(length);

    // read digital input
    for (int i = 0; i < length; i++) {
        // write one boolean (1 bit) to the response buffer.
        int bt = 0;
        if (i == 0) bt = digitalRead(5);
        slave.writeCoilToBuffer(i, bt);
    }

    return STATUS_OK;
}

/**
 * Handle Force Single Coil (FC=05) and Force Multiple Coils (FC=15)
 * set digital output pins (coils).
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
