#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

constexpr auto baudrate { 19200 }; 
constexpr auto btime { 1.0f / baudrate };
constexpr auto predl { btime * 9.6f * 3.5f * 1e6 };
constexpr auto postdl { btime * 9.6f * 3.5f * 1e6 };

void setup() {
  Serial.begin(115200);
  delay(2000);
  RS485.setDelays(predl, postdl);
  if (!ModbusRTUClient.begin(baudrate, SERIAL_8N2 ) ) {
    Serial.println("errore modbus");
    while(1);
  }

}

void loop() {
  //0x09BA - Active Power Total 32490-32491, IEEE 754 T_Float, x 1W
  float p = readdata(0x21, 0X9BA);
  //0x09C4 - Tensione 32500-32501, IEEE 754 T_Float, x 
  float v = readdata(0x21, 0X9C4);
  // 0x9D4 - corrente 32516-32517, IEEE 754 T_Float, x 1A
  float i = readdata(0x21, 0X9D4);

  Serial.println(String(p, 1) + "W " + String(v, 1) + "V " + String(i, 3) + "A ");
  delay(3000);
}


float readdata(int addr, int reg) {
  float res = 0.0;
  if (!ModbusRTUClient.requestFrom(addr, INPUT_REGISTERS, reg, 2)) {
    Serial.println("errore com");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    uint32_t parz = word1 << 16 | word2;
    res = *(float *)&parz;
  }
  return res;
}

