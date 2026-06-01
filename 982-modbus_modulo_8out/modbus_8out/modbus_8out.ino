#include <SoftwareSerial.h>
#include <RS485.h>

// https://github.com/RobTillaart/RS485

/*
Channel 1 Open ：01 06 00 01 01 00 D9 9A
Channel 1 Close ：01 06 00 01 02 00 D9 6A
Channel 1 Toggle：01 06 00 01 03 00 D8 FA
Channel 1 Latch：01 06 00 01 04 00 DA CA
Channel 1 Momentary: 01 06 00 01 05 00 DB 5A
Channel 1 Delay 10 seconds : 01 06 00 01 06 0A 5B AD
Channel 1 Delay 100 seconds: 01 06 00 01 06 64 DA 41

Channel 2 Open ：01 06 00 02 01 00 29 9A
Channel 2 Close ：01 06 00 02 02 00 29 6A
Channel 2 Toggle ：01 06 00 02 03 00 28 FA
Channel 2 Latch ：01 06 00 02 04 00 2A CA
Channel 2 Momentary : 01 06 00 02 05 00 2B 5A
Channel 2 Delay 10 seconds  : 01 06 00 02 06 0A AB AD
Channel 2 Delay 100 seconds : 01 06 00 02 06 64 2A 41

Read state (assuming that the channel 1 is open, the channel 2 is close).
Read channel 1 state ：01 03 00 01 00 01 D5 CA
Return open：01 03 02 00 01 79 84

Read channel 2 state ：01 03 00 02 00 01 25 CA
Return close：01 03 02 00 00 B8 44
*/

#define RX_PIN    4
#define TX_PIN    2
#define CTRL_PIN  3

uint8_t device = 1;

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);
RS485 rs485(&rs485Serial, CTRL_PIN);

void setup() {
  Serial.begin(115200);
  rs485Serial.begin(9600);
  // opzionale
  rs485.setMicrosPerByte(1100);

  Serial.println("RS485 - N4DIG08"); 
}

void loop() {
  writeRegister(device, 0x0001, 0x0100);
  writeRegister(device, 0x0007, 0x0100);
  readResponse();
  delay(1000);
  writeRegister(device, 0x0001, 0x0200);
  writeRegister(device, 0x0007, 0x0200);
  readResponse();
  delay(1000);
}

void writeRegister(uint8_t slave, uint16_t address, uint16_t value) {
  uint8_t frame[6];
  frame[0] = slave;
  frame[1] = 0x06; //write register
  frame[2] = highByte(address);
  frame[3] = lowByte(address);
  frame[4] = highByte(value);
  frame[5] = lowByte(value);
  sendModbusFrame(frame, 6);
}

void sendModbusFrame(uint8_t *frame, uint8_t len){
  uint16_t crc = modbusCRC(frame, len);
  digitalWrite(CTRL_PIN, HIGH);
  delayMicroseconds(100);
  for (uint8_t i = 0; i < len; i++) {
    rs485.write(frame[i]);
  }
  rs485.write(lowByte(crc));
  rs485.write(highByte(crc));
  rs485.flush();
  delayMicroseconds(100);
  digitalWrite(CTRL_PIN, LOW);
}

//--------------------------------------------------
// funzione per il calcolo del CRC16 per MODBUS
//--------------------------------------------------
uint16_t modbusCRC(uint8_t *buf, uint8_t len) {
  uint16_t crc = 0xFFFF;
  for (uint8_t pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];
    for (uint8_t i = 0; i < 8; i++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

void readResponse() {
  uint8_t response[8];
  uint8_t index = 0;

  while(rs485.available() && (index < 8)) {
    response[index] = rs485.read();
    index++;
  }

  if (index < 8) {
      Serial.println("RS485 - error"); 
      return;
  }

  for (int i = 0; i < 8; i++) {
    Serial.print(response[i], HEX);
    Serial.print(" "); 
  }
  Serial.print("\n"); 
}


