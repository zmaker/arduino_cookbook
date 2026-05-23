// https://github.com/RobTillaart/RS485
// read coil: FF 02 00 00 00 08 6C 12
/*	
FF	  slave id (addr)	
02	  Read Discrete Inputs (il comando)
00 00	indirizzo iniziale	
00 08	leggi 8 ingressi	
6C 12	CRC

La risposta:
FF 02 01 01 51 A0

FF	  slave
02	  funzione
01	  numero byte dati
01	  stato ingressi
51 A0	CRC
*/
typedef union {
  uint8_t all;
  struct {
    uint8_t IN1 : 1;
    uint8_t IN2 : 1;
    uint8_t IN3 : 1;
    uint8_t IN4 : 1;
    uint8_t IN5 : 1;
    uint8_t IN6 : 1;
    uint8_t IN7 : 1;
    uint8_t IN8 : 1;
  } bits;
} InputRegister;

#include <RS485.h>
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 2
#define CTRL_PIN 3

uint8_t device = 255;
uint16_t input_address = 0; //indirizzo dell'ingresso da leggere

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);
RS485 rs485(&rs485Serial, CTRL_PIN);

void setup() {
  Serial.begin(115200);
  rs485Serial.begin(9600);

  rs485.setMicrosPerByte(1100);
  Serial.println("RS485 rele 1");

  pinMode(13, OUTPUT);
}

void loop() {
  InputRegister in;

  in.all = readInput(device, input_address);

  if (in.bits.IN1) {
    Serial.println("ON");
    digitalWrite(13, HIGH);
  } else {
    Serial.println("OFF");
    digitalWrite(13, LOW);
  }

  delay(1000);
}

//legge 8 valori di ingresso all'indirizzo specificato
uint8_t readInput(uint8_t slave_addr, uint16_t in_addr){
  uint8_t frame[6];
  frame[0] = slave_addr;
  frame[1] = 0x02; 
  frame[2] = highByte(in_addr);
  frame[3] = lowByte(in_addr);
  frame[4] = 0x00;
  frame[5] = 0x08;
  sendModbusFrame(frame, 6);
  delay(50);

  uint8_t response[6];
  uint8_t index = 0;

  while(rs485.available() && index < 6) {
    response[index] = rs485.read();
    index++;
  }

  if (index < 6) {
    Serial.println("errore dati");
    return 0;
  }

  return response[3];
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

  frame[2] = highByte(coil_addr);
  frame[3] = lowByte(coil_addr);

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
