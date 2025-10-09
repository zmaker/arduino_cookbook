#ifndef _SPI_H_
#define _SPI_H_

#include <Arduino.h>

//项目板子
#define SCK 12
#define MOSI 11
#define RES 47
#define DC 46
#define CS 45
#define BUSY 48

//#define SCK 12
//#define MOSI 11
//#define RES 21
//#define DC 9
//#define CS 10
//#define BUSY 48

#define EPD_SCK_Clr() digitalWrite(SCK, LOW)
#define EPD_SCK_Set() digitalWrite(SCK, HIGH)

#define EPD_MOSI_Clr() digitalWrite(MOSI, LOW)
#define EPD_MOSI_Set() digitalWrite(MOSI, HIGH)

#define EPD_RES_Clr() digitalWrite(RES, LOW)
#define EPD_RES_Set() digitalWrite(RES, HIGH)

#define EPD_DC_Clr() digitalWrite(DC, LOW)
#define EPD_DC_Set() digitalWrite(DC, HIGH)

#define EPD_CS_Clr() digitalWrite(CS, LOW)
#define EPD_CS_Set() digitalWrite(CS, HIGH)

#define EPD_ReadBUSY digitalRead(BUSY)

void EPD_GPIOInit(void);
void EPD_WR_Bus(uint8_t dat);
void EPD_WR_REG(uint8_t reg);
void EPD_WR_DATA8(uint8_t dat);

#endif
