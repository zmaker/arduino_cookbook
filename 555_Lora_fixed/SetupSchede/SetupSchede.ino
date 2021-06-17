#include "Arduino.h"
#include "LoRa_E32.h"
 
LoRa_E32 e32ttl100(3, 2); // e32 TX e32 RX
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
 
void setup() {
  Serial.begin(9600);
  e32ttl100.begin();
  delay(100);
  
  ResponseStructContainer c;
  c = e32ttl100.getConfiguration();
  // It's important get configuration pointer before all other operation
  Configuration configuration = *(Configuration*) c.data;
  Serial.println(c.status.getResponseDescription());
  Serial.println(c.status.code);
  printParameters(configuration);

  configuration.ADDH = 0x0;  
  configuration.ADDL = 0x2;
  //configuration.CHAN = 0x06;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;

  /*configuration.OPTION.fec = FEC_1_ON;
  
  configuration.OPTION.ioDriveMode = IO_D_MODE_OPEN_COLLECTOR; //IO_D_MODE_PUSH_PULLS_PULL_UPS;
  configuration.OPTION.transmissionPower = POWER_17;
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_1250;
  
  configuration.SPED.airDataRate = AIR_DATA_RATE_011_48; 
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;
  */

  ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);  //LOSE
 
  ResponseStructContainer cMi;
  cMi = e32ttl100.getModuleInformation();
  
  // It's important get information pointer before all other operation
  ModuleInformation mi = *(ModuleInformation*)cMi.data;
 
  Serial.println(cMi.status.getResponseDescription());
  Serial.println(cMi.status.code);
 
  printModuleInformation(mi);

  //e32ttl100.setMode(MODE_0_NORMAL);
  e32ttl100.begin();
}
 
void loop() {}

void printParameters(struct Configuration configuration) {
    Serial.println("----------------------------------------");
 
    Serial.print(F("HEAD BIN: "));  Serial.print(configuration.HEAD);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
    Serial.println(F(" "));
    Serial.print(F("AddH BIN: "));  Serial.println(configuration.ADDH);
    Serial.print(F("AddL BIN: "));  Serial.println(configuration.ADDL);
    Serial.print(F("Chan BIN: "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("SpeedParityBit BIN    : "));  Serial.print(configuration.SPED.uartParity, DEC);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUARTDataRate BIN : "));  Serial.print(configuration.SPED.uartBaudRate, DEC);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
    Serial.print(F("SpeedAirDataRate BIN  : "));  Serial.print(configuration.SPED.airDataRate, DEC);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());
 
    Serial.print(F("OptionTrans BIN       : "));  Serial.print(configuration.OPTION.fixedTransmission, DEC);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
    Serial.print(F("OptionPullup BIN      : "));  Serial.print(configuration.OPTION.ioDriveMode, DEC);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
    Serial.print(F("OptionWakeup BIN      : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, DEC);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
    Serial.print(F("OptionFEC BIN         : "));  Serial.print(configuration.OPTION.fec, DEC);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
    Serial.print(F("OptionPower BIN       : "));  Serial.print(configuration.OPTION.transmissionPower, DEC);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
 
    Serial.println("----------------------------------------");
 
}
void printModuleInformation(struct ModuleInformation moduleInformation) {
    Serial.println("----------------------------------------");
    Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);
 
    Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
    Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
    Serial.println("----------------------------------------");
 
}
