#include <RS485.h>
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 2
#define CTRL_PIN 3

uint8_t device = 255;
uint16_t coil = 0;

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);
RS485 rs485(&rs485Serial, CTRL_PIN);

void setup() {
  Serial.begin(115200);
  rs485Serial.begin(9600);

  rs485.setMicrosPerByte(1100);
  Serial.println("RS485 rele 1");
}

void loop() {
  writeSingleCoil(device, coil, true);
  delay(1000);
  writeSingleCoil(device, coil, false);
  delay(2000);
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

//--------------------------------------------------
// WRITE SINGLE COIL
//--------------------------------------------------
void writeSingleCoil(uint8_t slave_addr, uint16_t coil_addr, bool stato){
  uint8_t frame[6];
  frame[0] = slave_addr;
  frame[1] = 0x05; 

  frame[2] = highByte(coil);
  frame[3] = lowByte(coil);

  if (stato) {
    frame[4] = 0xFF;
    frame[5] = 0x00;
  } else {
    frame[4] = 0x00;
    frame[5] = 0x00;
  }
  sendModbusFrame(frame, 6);
}

//--------------------------------------------------
// INVIO FRAME MODBUS
//--------------------------------------------------
void sendModbusFrame(uint8_t *frame, uint8_t len) {
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
