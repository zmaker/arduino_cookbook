#ifndef DHT_H
#define DHT_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>

// 8 MHz(ish) AVR ---------------------------------------------------------
#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)
#define COUNT 3
// 16 MHz(ish) AVR --------------------------------------------------------
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)
#define COUNT 6
// 48MHz SAMD21J18A (Sodaq Explorer)
#elif (F_CPU == 48000000UL)
#define COUNT 18
// 168MHz STM32F405 STM32F407
#elif (F_CPU == 168000000L)
#define COUNT 40
#elif (F_CPU == 80000000L)
#define COUNT 22
#elif (F_CPU == 160000000L)
#define COUNT 36
#else
#define COUNT 25
//#error "CPU SPEED NOT SUPPORTED"
#endif

/* DHT library

MIT license
written by Adafruit Industries
*/

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85
#define SERIALPRINT Serial

#define DEFAULT_IIC_ADDR    0x38
#define RESET_REG_ADDR      0xba
#define  HUMIDITY_INDEX     0
#define  TEMPRATURE_INDEX   1

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

#define DHT10 10

class DHT {
 private:
  uint8_t data[6];
  uint8_t _pin, _type, _count;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  DHT(uint8_t pin, uint8_t type, uint8_t count=COUNT);
  void begin(void);
  float readTemperature(bool S=false);
  float convertCtoF(float);
  float readHumidity(void);

  /**Common  interface to get temp&humi value.support all DHT device.
   * 
   * @return 0 for calibrated failed,1 for succeed.
   **/
  int readTempAndHumidity(float *data);

// DHT10 digital interfaces(i2c),onlu for DHT10 .
  int i2cReadByte(uint8_t& byte);
  int i2cReadBytes(uint8_t *bytes,uint32_t len);
  int i2cWriteBytes(uint8_t *bytes,uint32_t len);
  int i2cWriteByte(uint8_t byte);


  /**Reset sensor.
   * @return 0 for calibrated failed,1 for succeed.
   **/
  int DHT10Reset(void);

  /** Read status register.check the calibration flag - bit[3]: 1- calibrated ok ,0 - Not calibrated.
   * 
   * @return 0 for calibrated failed,1 for succeed. 
   * 
   **/
  int DHT10ReadStatus(void);
  /** Init sensor,send 0x08,0x00 to register 0xe1.
   *  @ return : 0 if success, non-zero if failed.
   **/
  int setSystemCfg(void);

  /** Read temp & humi result buf from sensor.
   *  total 6 bytes,the first byte for status register,other 5 bytes for temp & humidity data.
   *  @ return : 0 if success, non-zero if failed.
   **/
  int readTargetData(uint32_t *data);
  
  /**DHT10 Init function.
   * Reset sensor and wait for calibration complete.
   * @ return : 0 if success, non-zero if failed.
   **/ 
  int DHT10Init(void);


};
#endif
