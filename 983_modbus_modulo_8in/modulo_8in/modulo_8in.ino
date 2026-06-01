// https://github.com/RobTillaart/RS485

#include <SoftwareSerial.h>
#include <RS485.h>

#define RX_PIN    4
#define TX_PIN    2
#define CTRL_PIN  3

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);
// crea oggetto RS485
RS485 rs485(&rs485Serial, CTRL_PIN);

uint8_t device = 1;

void setup() {
  Serial.begin(115200);
  rs485Serial.begin(9600);
  
  // opzionale
  rs485.setMicrosPerByte(1100);
  Serial.println("RS485 start");

  pinMode(13, OUTPUT);
}

void loop() {
  readRegister(device, 0x0081, 0x0001); //0x0081 indirizzo primo ingresso - leggo 1 byte
  readResponse();
  delay(1000);
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


void readRegister(uint8_t slave, uint16_t reg_address, uint16_t bytes_to_read){
  uint8_t frame[6];
  frame[0] = slave;
  frame[1] = 0x03;
  frame[2] = highByte(reg_address);
  frame[3] = lowByte(reg_address);
  frame[4] = highByte(bytes_to_read);
  frame[5] = lowByte(bytes_to_read);

  sendModbusFrame(frame, 6);
}

//--------------------------------------------------
// INVIO FRAME MODBUS
//--------------------------------------------------
void sendModbusFrame(uint8_t *frame, uint8_t len) {
  uint16_t crc = modbusCRC(frame, len);

  digitalWrite(CTRL_PIN, HIGH);   // TX ENABLE
  delayMicroseconds(100);

  // invio dati
  for (uint8_t i = 0; i < len; i++) {
    rs485.write(frame[i]);
  }

  // CRC LOW BYTE
  rs485.write(lowByte(crc));
  // CRC HIGH BYTE
  rs485.write(highByte(crc));

  rs485.flush();

  delayMicroseconds(100);
  digitalWrite(CTRL_PIN, LOW);    // RX ENABLE
}

void readResponse(){
  uint8_t response[20];
  uint8_t bytes_ricevuti = 0;
  uint32_t startTime = millis();

  while (bytes_ricevuti < 3) {
    if (rs485.available()) {
      response[bytes_ricevuti] = rs485.read();
      bytes_ricevuti++;
    }

    if ((millis() - startTime) > 1000) {
      return;
    }
  }

  if (response[1] != 0x03) {
    return;
  }

  uint8_t byteCount = response[2];
  uint16_t expectedLen = 5 + byteCount;

  while (bytes_ricevuti < expectedLen) {
    if (rs485.available()) {
      response[bytes_ricevuti] = rs485.read();
      bytes_ricevuti++;
    }
    if ((millis() - startTime) > 1000) {
      return;
    }
  }

  for (int i = 0; i < bytes_ricevuti; i++){
    Serial.print(response[i], HEX); Serial.print(" ");
  }
  Serial.print("\n");

  digitalWrite(13, response[4]);
}
