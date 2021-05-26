/**
 ******************************************************************************
 * @file    vr_sample_train.ino
 * @author  JiapengLi
 * @brief   This file provides a demostration on 
 * how to train VoiceRecognitionModule to record your voice
 ******************************************************************************
 * @note:
 * Use serial command to control VoiceRecognitionModule. '
 * All commands are case insensitive. Default serial baud rate 115200.
 * 
 * COMMAND        FORMAT                        EXAMPLE                    Comment
 * 
 * train          train (r0) (r1)...            train 0 2 45               Train records
 * load           load (r0) (r1) ...            load 0 51 2 3              Load records
 * clear          clear                         clear                      remove all records in  Recognizer
 * record         record / record (r0) (r1)...  record / record 0 79       Check record train status
 * vr             vr                            vr                         Check recognizer status
 * getsig         getsig (r)                    getsig 0                   Get signature of record (r)
 * sigtrain       sigtrain (r) (sig)            sigtrain 0 ZERO            Train one record(r) with signature(sig)
 * settings       settings                      settings                   Check current system settings
 ******************************************************************************
 * @section  HISTORY
 * 
 * 2013/06/13    Initial version.
 */
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
 * Connection
 * Arduino    VoiceRecognitionModule
 * 2   ------->     TX
 * 3   ------->     RX
 */
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

/***************************************************************************/
/** declare print functions */
void printSeperator();
void printSignature(uint8_t *buf, int len);
void printVR(uint8_t *buf);
void printLoad(uint8_t *buf, uint8_t len);
void printTrain(uint8_t *buf, uint8_t len);
void printCheckRecognizer(uint8_t *buf);
void printUserGroup(uint8_t *buf, int len);
void printCheckRecord(uint8_t *buf, int num);
void printCheckRecordAll(uint8_t *buf, int num);
void printSigTrain(uint8_t *buf, uint8_t len);
void printSystemSettings(uint8_t *buf, int len);
void printHelp(void);

/***************************************************************************/
// command analyze part
#define CMD_BUF_LEN      64+1
#define CMD_NUM     10
typedef int (*cmd_function_t)(int, int);
uint8_t cmd[CMD_BUF_LEN];
uint8_t cmd_cnt;
uint8_t *paraAddr;
int receiveCMD();
int checkCMD(int len);
int checkParaNum(int len);
int findPara(int len, int paraNum, uint8_t **addr);
int compareCMD(uint8_t *para1 , uint8_t *para2, int len);

int cmdTrain(int len, int paraNum);
int cmdLoad(int len, int paraNum);
int cmdTest(int len, int paraNum);
int cmdVR(int len, int paraNum);
int cmdClear(int len, int paraNum);
int cmdRecord(int len, int paraNum);
int cmdSigTrain(int len, int paraNum);
int cmdGetSig(int len, int paraNum);
int cmdSettings(int len, int paraNum);
int cmdHelp(int len, int paraNum);
/** cmdList, cmdLen, cmdFunction has correspondence */
const char cmdList[CMD_NUM][10] = {  // command list table
  {
    "train"  }
  ,
  {
    "load"  }
  , 
  {
    "clear"  }
  ,
  {
    "vr"  }
  ,
  {
    "record"  }
  ,
  {
    "sigtrain"  }
  ,
  {
    "getsig"  }
  ,
  {
    "Settings"  }
  ,
  {
    "test"  }
  ,
  {
    "help"  }
  ,
};
const char cmdLen[CMD_NUM]= {    // command length
  5,  //  {"train"},
  4,  //  {"load"}, 
  5,  //  {"clear"},
  2,  //  {"vr"},
  6,  //  {"record"},
  8,  //  {"sigtrain"},
  6,  //  {"getsig"},
  8,  //  {"Settings"},
  4,  //  {"test"},
  4,  //  {"help"}
};
cmd_function_t cmdFunction[CMD_NUM]={      // command handle fuction(function pointer table)
  cmdTrain,
  cmdLoad,
  cmdClear,
  cmdVR,
  cmdRecord,
  cmdSigTrain,
  cmdGetSig,
  cmdSettings,
  cmdTest,
  cmdHelp,
};

/***************************************************************************/
/** temprory data */
uint8_t buf[255];
uint8_t records[7]; // save record

void setup(void)
{
  myVR.begin(9600);

  /** initialize */
  Serial.begin(115200);
  Serial.println(F("Elechouse Voice Recognition V3 Module \"train\" sample."));

  printSeperator();
  Serial.println(F("Usage:"));
  printSeperator();
  printHelp();
  printSeperator();
  cmd_cnt = 0;
}

void loop(void)
{
  int len, paraNum, paraLen, i;

  /** receive Serial command */
  len = receiveCMD();
  if(len>0){
    /** check if the received command is valid */
    if(!checkCMD(len)){

      /** check parameter number of the received command  */
      paraNum = checkParaNum(len);

      /** display the receved command back */
      Serial.write(cmd, len);

      /** find the first parameter */
      paraLen = findPara(len, 1, &paraAddr);

      /** compare the received command with command in the list */
      for(i=0; i<CMD_NUM; i++){
        /** compare command length */
        if(paraLen == cmdLen[i]){
          /** compare command content */
          if( compareCMD(paraAddr, (uint8_t *)cmdList[i], paraLen) == 0 ){
            /** call command function */
            if( cmdFunction[i](len, paraNum) != 0){
              printSeperator();
              Serial.println(F("Command Format Error!"));
              printSeperator();
            }
            break;
          }
        }
      }

      /** command is not supported*/
      if(i == CMD_NUM){ 
        printSeperator();
        Serial.println(F("Unkonwn command"));
        printSeperator();
      }
    }
    else{
      /** received command is invalid */
      printSeperator();
      Serial.println(F("Command format error"));
      printSeperator();
    }
  }

  /** try to receive recognize result */
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    /** voice recognized, print result */
    printVR(buf);
  }
}

/**
 * @brief   receive command from Serial.
 * @param   NONE.
 * @retval  command length, if no command receive return -1.
 */
int receiveCMD()
{
  int ret;
  int len;
  unsigned long start_millis;
  start_millis = millis();
  while(1){
    ret = Serial.read();
    if(ret>0){
      start_millis = millis();
      cmd[cmd_cnt] = ret;
      if(cmd[cmd_cnt] == '\n'){
        len = cmd_cnt+1;
        cmd_cnt = 0;
        return len;
      }
      cmd_cnt++;
      if(cmd_cnt == CMD_BUF_LEN){
        cmd_cnt = 0;
        return -1;
      }
    }

    if(millis() - start_millis > 100){
      cmd_cnt = 0;
      return -1;
    }
  }
}

/**
 * @brief   compare two commands, case insensitive.
 * @param   para1  -->  command buffer 1
 * para2  -->  command buffer 2
 * len    -->  buffer length
 * @retval  0  --> equal
 * -1  --> unequal
 */
int compareCMD(uint8_t *para1 , uint8_t *para2, int len)
{
  int i;
  uint8_t res;
  for(i=0; i<len; i++){
    res = para2[i] - para1[i];
    if(res != 0 && res != 0x20){
      res = para1[i] - para2[i];
      if(res != 0 && res != 0x20){
        return -1;
      }
    }
  }
  return 0;
}

/**
 * @brief   Check command format.
 * @param   len  -->  command length
 * @retval  0  -->  command is valid
 * -1  -->  command is invalid
 */
int checkCMD(int len)
{
  int i;
  for(i=0; i<len; i++){
    if(cmd[i] > 0x1F && cmd[i] < 0x7F){

    }
    else if(cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '\r' || cmd[i] == '\n'){

    }
    else{
      return -1;
    }
  }
  return 0;
}

/**
 * @brief   Check the number of parameters in the command
 * @param   len  -->  command length
 * @retval  number of parameters
 */
int checkParaNum(int len)
{
  int cnt=0, i;
  for(i=0; i<len; ){
    if(cmd[i]!='\t' && cmd[i]!=' ' && cmd[i] != '\r' && cmd[i] != '\n'){
      cnt++;
      while(cmd[i] != '\t' && cmd[i] != ' ' && cmd[i] != '\r' && cmd[i] != '\n'){
        i++;
      }
    }
    i++;
  }
  return cnt;
}

/**
 * @brief   Find the specified parameter.
 * @param   len       -->  command length
 * paraIndex -->  parameter index
 * addr      -->  return value. position of the parameter
 * @retval  length of specified parameter
 */
int findPara(int len, int paraIndex, uint8_t **addr)
{
  int cnt=0, i, paraLen;
  uint8_t dt;
  for(i=0; i<len; ){
    dt = cmd[i];
    if(dt!='\t' && dt!=' '){
      cnt++;
      if(paraIndex == cnt){
        *addr = cmd+i;
        paraLen = 0;
        while(cmd[i] != '\t' && cmd[i] != ' ' && cmd[i] != '\r' && cmd[i] != '\n'){
          i++;
          paraLen++;
        }
        return paraLen;
      }
      else{
        while(cmd[i] != '\t' && cmd[i] != ' ' && cmd[i] != '\r' && cmd[i] != '\n'){
          i++;
        }
      }
    }
    else{
      i++;
    }
  }
  return -1;
}

int cmdHelp(int len, int paraNum)
{
  if(paraNum != 1){
    return -1;
  }
  printSeperator();
  printHelp();
  printSeperator();
  return 0;
}

/**
 * @brief   Handle "train" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdTrain(int len, int paraNum)
{
  int i, ret;
  if(paraNum < 2 || paraNum > 8 ){
    return -1;
  }

  for(i=2; i<=paraNum; i++){
    findPara(len, i, &paraAddr);
    records[i-2] = atoi((char *)paraAddr);
    if(records[i-2] == 0 && *paraAddr != '0'){
      return -1;
    }
  }
  printSeperator();
  ret = myVR.train(records, paraNum-1, buf);
  //  ret = myVR.train(records, paraNum-1);
  if(ret >= 0){
    printTrain(buf, ret);
  }
  else if(ret == -1){
    Serial.println(F("Train failed."));
  }
  else if(ret == -2){
    Serial.println(F("Train Timeout."));
  }
  printSeperator();
  return 0;
}

/**
 * @brief   Handle "load" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdLoad(int len, int paraNum)
{
  int i, ret;
  if(paraNum < 2 || paraNum > 8 ){
    return -1;
  }

  for(i=2; i<=paraNum; i++){
    findPara(len, i, &paraAddr);
    records[i-2] = atoi((char *)paraAddr);
    if(records[i-2] == 0 && *paraAddr != '0'){
      return -1;
    }
  }
  //  myVR.writehex(records, paraNum-1);
  ret = myVR.load(records, paraNum-1, buf);
  printSeperator();
  if(ret >= 0){
    printLoad(buf, ret);
  }
  else{
    Serial.println(F("Load failed or timeout."));
  }
  printSeperator();
  return 0;
}

/**
 * @brief   Handle "clear" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdClear(int len, int paraNum)
{
  if(paraNum != 1){
    return -1;
  }
  if(myVR.clear() == 0){
    printSeperator();
    Serial.println(F("Recognizer cleared."));
    printSeperator();
  }
  else{
    printSeperator();
    Serial.println(F("Clear recognizer failed or timeout."));
    printSeperator();
  }
  return 0;
}

/**
 * @brief   Handle "vr" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdVR(int len, int paraNum)
{
  int ret;
  if(paraNum != 1){
    return -1;
  }
  ret = myVR.checkRecognizer(buf);
  if(ret<=0){
    printSeperator();
    Serial.println(F("Check recognizer failed or timeout."));
    printSeperator();
    return 0;
  }
  printSeperator();
  printCheckRecognizer(buf);
  printSeperator();
  return 0;
}

/**
 * @brief   Handle "record" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdRecord(int len, int paraNum)
{
  int ret;
  if(paraNum == 1){
    ret = myVR.checkRecord(buf);
    printSeperator();
    if(ret>=0){
      printCheckRecordAll(buf, ret);
    }
    else{
      Serial.println(F("Check record failed or timeout."));
    }
    printSeperator();
  }
  else if(paraNum < 9){
    for(int i=2; i<=paraNum; i++){
      findPara(len, i, &paraAddr);
      records[i-2] = atoi((char *)paraAddr);
      if(records[i-2] == 0 && *paraAddr != '0'){
        return -1;
      }      
    }

    ret = myVR.checkRecord(buf, records, paraNum-1);    // auto clean duplicate records
    printSeperator();
    if(ret>=0){
      printCheckRecord(buf, ret);
    }
    else{
      Serial.println(F("Check record failed or timeout."));
    }
    printSeperator();
  }
  else{
    return -1;
  }
  return 0;
}

/**
 * @brief   Handle "sigtrain" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdSigTrain(int len, int paraNum)
{
  int ret, sig_len;
  uint8_t *lastAddr;
  if(paraNum < 2){
    return -1;
  }

  findPara(len, 2, &paraAddr);
  records[0] = atoi((char *)paraAddr);
  if(records[0] == 0 && *paraAddr != '0'){
    return -1;
  }

  findPara(len, 3, &paraAddr);
  sig_len = findPara(len, paraNum, &lastAddr);
  sig_len +=( (unsigned int)lastAddr - (unsigned int)paraAddr );

  printSeperator();
  ret = myVR.trainWithSignature(records[0], paraAddr, sig_len, buf);
  //  ret = myVR.trainWithSignature(records, paraNum-1);
  if(ret >= 0){
    printSigTrain(buf, ret);
  }
  else{
    Serial.println(F("Train with signature failed or timeout."));
  }
  printSeperator();

  return 0;
}

/**
 * @brief   Handle "getsig" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdGetSig(int len, int paraNum)
{
  int ret;
  if(paraNum != 2){
    return -1;
  }

  findPara(len, 2, &paraAddr);
  records[0] = atoi((char *)paraAddr);
  if(records[0] == 0 && *paraAddr != '0'){
    return -1;
  }

  ret = myVR.checkSignature(records[0], buf);

  printSeperator();
  if(ret == 0){
    Serial.println(F("Signature isn't set."));
  }
  else if(ret > 0){
    Serial.print(F("Signature:"));
    printSignature(buf, ret);
    Serial.println();
  }
  else{
    Serial.println(F("Get sig error or timeout."));
  }
  printSeperator();

  return 0;
}

/**
 * @brief   Handle "test" command
 * @param   len     --> command length
 * paraNum --> number of parameters
 * @retval  0 --> success
 * -1 --> Command format error
 */
int cmdTest(int len, int paraNum)
{
  printSeperator();
  Serial.println(F("TEST is not supported."));
  printSeperator();
  return 0;
}

int cmdSettings(int len, int paraNum)
{
  int ret;
  if(paraNum != 1){
    return -1;
  }
  ret = myVR.checkSystemSettings(buf);
  if( ret > 0){
    printSeperator();
    printSystemSettings(buf, ret);
    printSeperator();
  }
  else{
    printSeperator();
    Serial.println(F("Check system settings error or timeout"));
    printSeperator();
  }
  return 0;
}

/*****************************************************************************/
/**
 * @brief   Print signature, if the character is invisible, 
 * print hexible value instead.
 * @param   buf     --> command length
 * len     --> number of parameters
 */
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print(F("["));
      Serial.print(buf[i], HEX);
      Serial.print(F("]"));
    }
  }
}

/**
 * @brief   Print signature, if the character is invisible, 
 * print hexible value instead.
 * @param   buf  -->  VR module return value when voice is recognized.
 * buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
 * buf[1]  -->  number of record which is recognized. 
 * buf[2]  -->  Recognizer index(position) value of the recognized record.
 * buf[3]  -->  Signature length
 * buf[4]~buf[n] --> Signature
 */
void printVR(uint8_t *buf)
{
  Serial.println(F("VR Index\tGroup\tRecordNum\tSignature"));

  Serial.print(buf[2], DEC);
  Serial.print(F("\t\t"));

  if(buf[0] == 0xFF){
    Serial.print(F("NONE"));
  }
  else if(buf[0]&0x80){
    Serial.print(F("UG "));
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print(F("SG "));
    Serial.print(buf[0], DEC);
  }
  Serial.print(F("\t"));

  Serial.print(buf[1], DEC);
  Serial.print(F("\t\t"));
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print(F("NONE"));
  }
  Serial.println(F("\r\n"));
}

/**
 * @brief   Print seperator. Print 80 '-'.
 */
void printSeperator()
{
  for(int i=0; i<80; i++){
    Serial.write('-');
  }
  Serial.println();
}

/**
 * @brief   Print recoginizer status.
 * @param   buf  -->  VR module return value when voice is recognized.
 * buf[0]     -->  Number of valid voice records in recognizer
 * buf[i+1]   -->  Record number.(0xFF: Not loaded(Nongroup mode), or not set (Group mode)) (i= 0, 1, ... 6)
 * buf[8]     -->  Number of all voice records in recognizer
 * buf[9]     -->  Valid records position indicate.
 * buf[10]    -->  Group mode indicate(FF: None Group, 0x8n: User, 0x0n:System)
 */
void printCheckRecognizer(uint8_t *buf)
{
  Serial.print(F("All voice records in recognizer: "));
  Serial.println(buf[8], DEC);
  Serial.print(F("Valid voice records in recognizer: "));
  Serial.println(buf[0], DEC);
  if(buf[10] == 0xFF){
    Serial.println(F("VR is not in group mode."));
  }
  else if(buf[10]&0x80){
    Serial.print(F("VR is in user group mode:"));
    Serial.println(buf[10]&0x7F, DEC);
  }
  else{
    Serial.print(F("VR is in system group mode:"));
    Serial.println(buf[10], DEC);
  }
  Serial.println(F("VR Index\tRecord\t\tComment"));
  for(int i=0; i<7; i++){
    Serial.print(i, DEC);
    Serial.print(F("\t\t"));
    if(buf[i+1] == 0xFF){
      if(buf[10] == 0xFF){
        Serial.print(F("Unloaded\tNONE"));
      }
      else{
        Serial.print(F("Not Set\t\tNONE"));
      }
    }
    else{
      Serial.print(buf[i+1], DEC);
      Serial.print(F("\t\t"));
      if(buf[9]&(1<<i)){
        Serial.print(F("Valid"));
      }
      else{
        Serial.print(F("Untrained"));
      }
    }

    Serial.println();
  } 
}

/**
 * @brief   Print record train status.
 * @param   buf  -->  Check record command return value
 * buf[0]     -->  Number of checked records
 * buf[2i+1]  -->  Record number.
 * buf[2i+2]  -->  Record train status. (00: untrained, 01: trained, FF: record value out of range)
 * (i = 0 ~ buf[0]-1 )
 * num  -->  Number of trained records
 */
void printCheckRecord(uint8_t *buf, int num)
{
  Serial.print(F("Check "));
  Serial.print(buf[0], DEC);
  Serial.println(F(" records."));

  Serial.print(num, DEC);
  if(num>1){
    Serial.println(F(" records trained."));
  }
  else{
    Serial.println(F(" record trained."));
  }

  for(int i=0; i<buf[0]*2; i += 2){
    Serial.print(buf[i+1], DEC);
    Serial.print(F("\t-->\t"));
    switch(buf[i+2]){
    case 0x01:
      Serial.print(F("Trained"));
      break;
    case 0x00:
      Serial.print(F("Untrained"));
      break;
    case 0xFF:
      Serial.print(F("Record value out of range"));
      break;
    default:
      Serial.print(F("Unknown Stauts"));
      break;
    }
    Serial.println();
  }
}

/**
 * @brief   Print record train status.
 * @param   buf  -->  Check record command return value
 * buf[0]     -->  Number of checked records
 * buf[2i+1]  -->  Record number.
 * buf[2i+2]  -->  Record train status. (00: untrained, 01: trained, FF: record value out of range)
 * (i = 0 ~ buf[0]-1 )
 * num  -->  Number of trained records
 */
void printCheckRecordAll(uint8_t *buf, int num)
{
  Serial.print(F("Check 255"));
  Serial.println(F(" records."));

  Serial.print(num, DEC);
  if(num>1){
    Serial.println(F(" records trained."));
  }
  else{
    Serial.println(F(" record trained."));
  }
  myVR.writehex(buf, 255);
  for(int i=0; i<255; i++){
    if(buf[i] == 0xF0){
      continue;
    }
    Serial.print(i, DEC);
    Serial.print(F("\t-->\t"));
    switch(buf[i]){
    case 0x01:
      Serial.print(F("Trained"));
      break;
    case 0x00:
      Serial.print(F("Untrained"));
      break;
    case 0xFF:
      Serial.print(F("Record value out of range"));
      break;
    default:
      Serial.print(F("Unknown Stauts"));
      break;
    }
    Serial.println();
  }
}

/**
 * @brief   Print check user group result.
 * @param   buf  -->  Check record command return value
 * buf[8i]    -->  group number.
 * buf[8i+1]  -->  group position 0 status.
 * buf[8i+2]  -->  group position 1 status.
 * ...                ...
 * buf[8i+6]  -->  group position 5 status.
 * buf[8i+7]  -->  group position 6 status.
 * (i = 0 ~ len)
 * len  -->  number of checked groups
 */
void printUserGroup(uint8_t *buf, int len)
{
  int i, j;
  Serial.println(F("Check User Group:"));
  for(i=0; i<len; i++){
    Serial.print(F("Group:"));
    Serial.println(buf[8*i]);
    for(j=0; j<7; j++){
      if(buf[8*i+1+j] == 0xFF){
        Serial.print(F("NONE\t"));
      }
      else{
        Serial.print(buf[8*i+1+j], DEC);
        Serial.print(F("\t"));
      }
    }
    Serial.println();
  }
}

/**
 * @brief   Print "load" command return value.
 * @param   buf  -->  "load" command return value
 * buf[0]    -->  number of records which are load successfully.
 * buf[2i+1]  -->  record number
 * buf[2i+2]  -->  record load status.
 * 00 --> Loaded 
 * FC --> Record already in recognizer
 * FD --> Recognizer full
 * FE --> Record untrained
 * FF --> Value out of range"
 * (i = 0 ~ (len-1)/2 )
 * len  -->  length of buf
 */
void printLoad(uint8_t *buf, uint8_t len)
{
  if(len == 0){
    Serial.println(F("Load Successfully."));
    return;
  }
  else{
    Serial.print(F("Load success: "));
    Serial.println(buf[0], DEC);
  }
  for(int i=0; i<len-1; i += 2){
    Serial.print(F("Record "));
    Serial.print(buf[i+1], DEC);
    Serial.print(F("\t"));
    switch(buf[i+2]){
    case 0:
      Serial.println(F("Loaded"));
      break;
    case 0xFC:
      Serial.println(F("Record already in recognizer"));
      break;
    case 0xFD:
      Serial.println(F("Recognizer full"));
      break;
    case 0xFE:
      Serial.println(F("Record untrained"));
      break;
    case 0xFF:
      Serial.println(F("Value out of range"));
      break;
    default:
      Serial.println(F("Unknown status"));
      break;
    }
  }
}

/**
 * @brief   Print "train" command return value.
 * @param   buf  -->  "train" command return value
 * buf[0]    -->  number of records which are trained successfully.
 * buf[2i+1]  -->  record number
 * buf[2i+2]  -->  record train status.
 * 00 --> Trained 
 * FE --> Train Time Out
 * FF --> Value out of range"
 * (i = 0 ~ len-1 )
 * len  -->  length of buf
 */
void printTrain(uint8_t *buf, uint8_t len)
{
  if(len == 0){
    Serial.println(F("Train Finish."));
    return;
  }
  else{
    Serial.print(F("Train success: "));
    Serial.println(buf[0], DEC);
  }
  for(int i=0; i<len-1; i += 2){
    Serial.print(F("Record "));
    Serial.print(buf[i+1], DEC);
    Serial.print(F("\t"));
    switch(buf[i+2]){
    case 0:
      Serial.println(F("Trained"));
      break;
    case 0xFE:
      Serial.println(F("Train Time Out"));
      break;
    case 0xFF:
      Serial.println(F("Value out of range"));
      break;
    default:
      Serial.print(F("Unknown status "));
      Serial.println(buf[i+2], HEX);
      break;
    }
  }
}

/**
 * @brief   Print "sigtrain" command return value.
 * @param   buf  -->  "sigtrain" command return value
 * buf[0]  -->  number of records which are trained successfully.
 * buf[1]  -->  record number
 * buf[2]  -->  record train status.
 * 00 --> Trained 
 * F0 --> Trained, signature truncate
 * FE --> Train Time Out
 * FF --> Value out of range"
 * buf[3] ~ buf[len-1] --> Signature.
 * len  -->  length of buf
 */
void printSigTrain(uint8_t *buf, uint8_t len)
{
  if(len == 0){
    Serial.println(F("Train With Signature Finish."));
    return;
  }
  else{
    Serial.print(F("Success: "));
    Serial.println(buf[0], DEC);
  }
  Serial.print(F("Record "));
  Serial.print(buf[1], DEC);
  Serial.print(F("\t"));
  switch(buf[2]){
  case 0:
    Serial.println(F("Trained"));
    break;
  case 0xF0:
    Serial.println(F("Trained, signature truncate"));
    break;
  case 0xFE:
    Serial.println(F("Train Time Out"));
    break;
  case 0xFF:
    Serial.println(F("Value out of range"));
    break;
  default:
    Serial.print(F("Unknown status "));
    Serial.println(buf[2], HEX);
    break;
  }
  Serial.print(F("SIG: "));
  Serial.write(buf+3, len-3);
  Serial.println();
}

/**
 * @brief   Print "settings" command return value.
 * @param   buf  -->  "settings" command return value
 * buf[0]  -->  number of records which are trained successfully.
 * buf[1]  -->  record number
 * buf[2]  -->  record train status.
 * 00 --> Trained 
 * F0 --> Trained, signature truncate
 * FE --> Train Time Out
 * FF --> Value out of range"
 * buf[3] ~ buf[len-1] --> Signature.
 * len  -->  length of buf
 */

const unsigned int io_pw_tab[16]={
  10,  15,  20,  25,  30,  35,  40,  45, 
  50,  75,  100, 200, 300, 400, 500, 1000
};

void printSystemSettings(uint8_t *buf, int len)
{

  switch(buf[0]){
  case 0:
  case 3:
    Serial.println(F("Baud rate: 9600"));
    break;
  case 1:
    Serial.println(F("Baud rate: 2400"));
    break;
  case 2:
    Serial.println(F("Baud rate: 4800"));
    break;
  case 4:
    Serial.println(F("Baud rate: 19200"));
    break;
  case 5:
    Serial.println(F("Baud rate: 38400"));
    break;
  default:
    Serial.println(F("Baud rate: UNKONOWN"));
    break;
  }

  switch(buf[1]){
  case 0:
  case 0xFF:
    Serial.println(F("Outpu IO Mode: Pulse"));
    break;
  case 1:
    Serial.println(F("Outpu IO Mode: Toggle"));
    break;
  case 2:
    Serial.println(F("Outpu IO Mode: Clear(When recognized) "));
    break;
  case 3:
    Serial.println(F("Outpu IO Mode: Set(When recognized)"));
    break;
  default:
    Serial.println(F("Output IO Mode: UNKONOWN"));
    break;
  }

  if(buf[2] > 15){
    Serial.println(F("Pulse width: UNKONOWN"));
  }
  else{
    Serial.print(F("Pulse Width: "));
    Serial.print(io_pw_tab[buf[2]], DEC);
    Serial.println(F("ms"));
  }

  if(buf[3] == 0 || buf[3] == 0xFF){
    Serial.println(F("Auto Load: disable"));
  }
  else{
    Serial.println(F("Auto Load: enable"));
  }

  switch(buf[4]){
  case 0:
  case 0xFF:
    Serial.println(F("Group control by external IO: disabled"));
    break;
  case 1:
    Serial.println(F("Group control by external IO: system group selected"));
    break;
  case 2:
    Serial.println(F("Group control by external IO: user group selected"));
    break;
  default:
    Serial.println(F("Group control by external IO: UNKNOWN STATUS"));
    break;
  }
}

void printHelp(void)
{
  Serial.println(F("COMMAND        FORMAT                        EXAMPLE                    Comment"));
  printSeperator();
  //  Serial.println(F("--------------------------------------------------------------------------------------------------------------"));
  Serial.println(F("train          train (r0) (r1)...            train 0 2 45               Train records"));
  Serial.println(F("load           load (r0) (r1) ...            load 0 51 2 3              Load records"));
  Serial.println(F("clear          clear                         clear                      remove all records in  Recognizer"));
  Serial.println(F("record         record / record (r0) (r1)...  record / record 0 79       Check record train status"));
  Serial.println(F("vr             vr                            vr                         Check recognizer status"));
  Serial.println(F("getsig         getsig (r)                    getsig 0                   Get signature of record (r)"));
  Serial.println(F("sigtrain       sigtrain (r) (sig)            sigtrain 0 ZERO            Train one record(r) with signature(sig)"));
  Serial.println(F("settings       settings                      settings                   Check current system settings"));
  Serial.println(F("help           help                          help                       print this message"));
}
