/* DHT library 

MIT license
written by Adafruit Industries
*/

#include <math.h>
#include "DHT.h"
//#define NAN 0
#ifdef DEBUG
#define DEBUG_PRINT(...)  Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif
DHT::DHT(uint8_t pin, uint8_t type, uint8_t count) {
  _pin = pin;
  _type = type;
  _count = count;
  firstreading = true;
}



void DHT::begin(void) {

  if(_type == DHT10){
    if(DHT10Init()){
        SERIALPRINT.println("Error : Failed to init DHT 11\n");
		    while(1);
    }
  }
  else{
    // set up the pins!
    pinMode(_pin, INPUT);
    digitalWrite(_pin, HIGH);
    _lastreadtime = 0;
  }

}

/**Common  interface to get temp&humi value.support all DHT device.
 * 
 * @return 0 for calibrated failed,1 for succeed.
 **/
int DHT::readTempAndHumidity(float *data)
{
    uint32_t target_val[2] = {0};
    uint32_t cnt;
    if(_type == DHT10){
      while(DHT10ReadStatus()==0)
      {
        DHT10Init();
        delay(30);
        cnt++;
        if(cnt > 3)
          return -1;
      }
        //wait for data ready。
        while(readTargetData(target_val)){
          cnt++;
          delay(50);
          if(cnt > 5){
            return -1;
          }

        }
        data[0] = target_val[0] *100.0/1024/1024;
        data[1] = target_val[1] *200.0/1024/1024-50;

    }
    else{
        data[0] = readHumidity();
        data[1] = readTemperature();
        if (isnan(data[0]) || isnan(data[1])){
            return -1;
        }
    }
    return 0;
}

//boolean S == Scale.  True == Farenheit; False == Celcius
float DHT::readTemperature(bool S) {
  float f;

  if (read()) {
    switch (_type) {
    case DHT11:
      f = data[2];
      if(S)
      	f = convertCtoF(f);
      	
      return f;
    case DHT22:
    case DHT21:
      f = data[2] & 0x7F;
      f *= 256;
      f += data[3];
      f /= 10;
      if (data[2] & 0x80)
	f *= -1;
      if(S)
	f = convertCtoF(f);

      return f;
    }
  }
  DEBUG_PRINT("Read fail");
  return NAN;
}

float DHT::convertCtoF(float c) {
	return c * 9 / 5 + 32;
}

float DHT::readHumidity(void) {
  float f;
  if (read()) {
    switch (_type) {
    case DHT11:
      f = data[0];
      return f;
    case DHT22:
    case DHT21:
      f = data[0];
      f *= 256;
      f += data[1];
      f /= 10;
      return f;
    }
  }
  DEBUG_PRINT("Read fail");
  return NAN;
}


boolean DHT::read(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long currenttime;

  // pull the pin high and wait 250 milliseconds
  digitalWrite(_pin, HIGH);
  delay(250);

  currenttime = millis();
  if (currenttime < _lastreadtime) {
    // ie there was a rollover
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; // return last correct measurement
    //delay(2000 - (currenttime - _lastreadtime));
  }
  firstreading = false;
  /*
    DEBUG_PRINT("Currtime: "); DEBUG_PRINT(currenttime);
    DEBUG_PRINT(" Lasttime: "); DEBUG_PRINT(_lastreadtime);
  */
  _lastreadtime = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // now pull it low for ~20 milliseconds
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(20);
  //cli();
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);

  // read in timings
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(_pin) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = digitalRead(_pin);

    if (counter == 255) break;

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > _count)
        data[j/8] |= 1;
      j++;
    }

  }

  //sei();
  
  /*
  DEBUG_PRINTln(j, DEC);
  DEBUG_PRINT(data[0], HEX); DEBUG_PRINT(", ");
  DEBUG_PRINT(data[1], HEX); DEBUG_PRINT(", ");
  DEBUG_PRINT(data[2], HEX); DEBUG_PRINT(", ");
  DEBUG_PRINT(data[3], HEX); DEBUG_PRINT(", ");
  DEBUG_PRINT(data[4], HEX); DEBUG_PRINT(" =? ");
  DEBUG_PRINTln(data[0] + data[1] + data[2] + data[3], HEX);
  */

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  

  return false;

}

/*****************************************************************************/
/*****************************************************************************/

/**Reset sensor.
 * @return 0 for calibrated failed,1 for succeed.
 **/
int DHT::DHT10Reset(void)
{
  if(_type == DHT10)
	    return i2cWriteByte(RESET_REG_ADDR);
  else{
      return 0;
      SERIALPRINT.println("This function only support for DHT10");
  } 

}

/** Read status register.check the calibration flag - bit[3]: 1- calibrated ok ,0 - Not calibrated.
 * 
 * @return 0 for calibrated failed,1 for succeed. 
 * 
 **/
int DHT::DHT10ReadStatus(void)
{

	int ret = 0;
	uint8_t statu = 0;
  if(_type == DHT10){
        ret = i2cReadByte(statu);
	    if(ret)
		    SERIALPRINT.println("Failed to read byte\n");
	    if((statu & 0x8)==0x8)  
  		  return 1;
  	  else  
	  	  return 0;
  }
  else{
        SERIALPRINT.println("This function only support for DHT10");
        return 0;
  }
    
}

/** Init sensor,send 0x08,0x00 to register 0xe1.
 *  @ return : 0 if success, non-zero if failed.
 **/
int DHT::setSystemCfg(void)
{
	uint8_t cfg_param[] = {0xe1,0x08,0x00};
  if(_type == DHT10)
	    return i2cWriteBytes(cfg_param,sizeof(cfg_param));
  else {
    SERIALPRINT.println("This function only support for DHT10");
    return 0;
  }
}


/** Read temp & humi result buf from sensor.
 *  total 6 bytes,the first byte for status register,other 5 bytes for temp & humidity data.
 *  @ return : 0 if success, non-zero if failed.
 **/
int DHT::readTargetData(uint32_t *data)
{
	uint8_t statu = 0;
	uint8_t bytes[6] = {0};
	uint8_t cfg_params[] ={0xac,0x33,0x00};
	int ret = 0;

  if(_type == DHT10){

    if( i2cWriteBytes(cfg_params,sizeof(cfg_params)) ){
      return -1;
    }

    delay(75);
    // check device busy flag， bit[7]:1 for busy, 0 for idle.
    while(statu & 0x80 == 0x80){
      SERIALPRINT.println("Device busy!");
      delay(200);
      if(i2cReadByte(statu)){
        return -1;
      }	
    }

    if(i2cReadBytes(bytes,sizeof(bytes))){
      return -1;
    }
    

    data[HUMIDITY_INDEX] = (data[HUMIDITY_INDEX] | bytes[1]) << 8;
    data[HUMIDITY_INDEX] = (data[HUMIDITY_INDEX] | bytes[2]) << 8;
    data[HUMIDITY_INDEX] = (data[HUMIDITY_INDEX] | bytes[3]);
    data[HUMIDITY_INDEX] = data[HUMIDITY_INDEX] >>4;

    data[TEMPRATURE_INDEX] = (data[TEMPRATURE_INDEX] | bytes[3]) << 8;
    data[TEMPRATURE_INDEX] = (data[TEMPRATURE_INDEX] | bytes[4]) << 8;
    data[TEMPRATURE_INDEX] = (data[TEMPRATURE_INDEX] | bytes[5]);
    data[TEMPRATURE_INDEX] &= 0xfffff;

    return 0;
  }
  else {
    SERIALPRINT.println("This function only support for DHT10");
    return 0;
  }
}

/**DHT10 Init function.
 * Reset sensor and wait for calibration complete.
 * @ return : 0 if success, non-zero if failed.
 **/ 
int DHT::DHT10Init(void)
{
	int ret = 0;
	int cnt = 0;

  if(_type == DHT10){

      delay(500);
      DHT10Reset();
      delay(300);
      
      ret = setSystemCfg();
      if(ret){
        SERIALPRINT.println("Failed to set system conf reg \n");
      }
      //SERIALPRINT.println("Set system cfg OK!");

      delay(500);
      
      while(DHT10ReadStatus()==0)
      {
        SERIALPRINT.println("get status error!");
        DHT10Reset();
        delay(500);
        if(setSystemCfg()){
          SERIALPRINT.println("Failed to set system conf reg \n");
        }
        delay(500);
        cnt++;
        if(cnt>5)
          return -1;
      }
      return 0;
  }
  else{
      SERIALPRINT.println("This function only support for DHT10");
      return 0;
  }
  
}



/*****************************************************************************/
/*****************************************************************************/

int DHT::i2cReadByte(uint8_t& byte)
{
	int cnt = 0;
	Wire.requestFrom(DEFAULT_IIC_ADDR,1);
	while(1 != Wire.available()){
		cnt++;
		if(cnt >= 10 )
			return -1;
		delay(1);
	}

	byte = Wire.read();
	return 0;
}

int DHT::i2cReadBytes(uint8_t *bytes,uint32_t len)
{
	int cnt = 0;
	Wire.requestFrom(DEFAULT_IIC_ADDR,len);
	while(len != Wire.available()){
		cnt++;
		if(cnt >= 10 )
			return -1;
		delay(1);
	}
	for(int i=0;i<len;i++){
		bytes[i] = Wire.read();
	}
	return 0;
}


int DHT::i2cWriteBytes(uint8_t *bytes,uint32_t len)
{
	Wire.beginTransmission(DEFAULT_IIC_ADDR);
	for(int i=0;i< len;i++)
	{
		Wire.write(bytes[i]);
	}
	return Wire.endTransmission();
}

int DHT::i2cWriteByte(uint8_t byte)
{
	Wire.beginTransmission(DEFAULT_IIC_ADDR);
	Wire.write(byte);
	return Wire.endTransmission();
}




