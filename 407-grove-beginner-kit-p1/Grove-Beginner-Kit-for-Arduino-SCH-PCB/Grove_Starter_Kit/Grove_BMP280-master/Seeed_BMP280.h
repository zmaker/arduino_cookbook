#ifndef _SEEED_BMP280_H_
#define _SEEED_BMP280_H_

#include <Arduino.h>
#include <Wire.h>

#define BMP280_ADDRESS   0x77

#define BMP280_REG_DIG_T1    0x88
#define BMP280_REG_DIG_T2    0x8A
#define BMP280_REG_DIG_T3    0x8C

#define BMP280_REG_DIG_P1    0x8E
#define BMP280_REG_DIG_P2    0x90
#define BMP280_REG_DIG_P3    0x92
#define BMP280_REG_DIG_P4    0x94
#define BMP280_REG_DIG_P5    0x96
#define BMP280_REG_DIG_P6    0x98
#define BMP280_REG_DIG_P7    0x9A
#define BMP280_REG_DIG_P8    0x9C
#define BMP280_REG_DIG_P9    0x9E

#define BMP280_REG_CHIPID          0xD0
#define BMP280_REG_VERSION         0xD1
#define BMP280_REG_SOFTRESET       0xE0

#define BMP280_REG_CONTROL         0xF4
#define BMP280_REG_CONFIG          0xF5
#define BMP280_REG_PRESSUREDATA    0xF7
#define BMP280_REG_TEMPDATA        0xFA

class BMP280 {
  public:
    bool init(int i2c_addr = BMP280_ADDRESS);
    float getTemperature(void);
    uint32_t getPressure(void);
    float calcAltitude(float pressure);
  private:
    bool isTransport_OK;
    int _devAddr;
    // Calibratino data
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
    int32_t t_fine;

    // private functoins
    uint8_t bmp280Read8(uint8_t reg);
    uint16_t bmp280Read16(uint8_t reg);
    uint16_t bmp280Read16LE(uint8_t reg);
    int16_t bmp280ReadS16(uint8_t reg);
    int16_t bmp280ReadS16LE(uint8_t reg);
    uint32_t bmp280Read24(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t val);
};

#endif
