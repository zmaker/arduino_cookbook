#include "HD44780_LCD_PCF8574.h"
HD44780LCD myLCD(2, 16, 0x26, &Wire);

#include <basic_dcf77.h>
#include <DebugProject.h>

uint8_t bitArray[DCF77_STRING_SIZE]; 
TimeStampDCF77 timex;

void setup() {
  Serial.begin(115200);
  myLCD.PCF8574_LCDInit(myLCD.LCDCursorTypeOn);
  myLCD.PCF8574_LCDClearScreen();
  myLCD.PCF8574_LCDBackLightSet(true);

  myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberOne, 0);
  myLCD.PCF8574_LCDSendString("DCF77 Receiver");
  delay(2000);
 
  setupDCF77(2);
}

void loop() {
  myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberTwo, 0);
  myLCD.PCF8574_LCDSendString("R");
  
  int ans = receiveDCF77(bitArray, DCF77_STRING_SIZE);

  if (ans == SUCCESS) {
    decodeDCF77(bitArray, DCF77_STRING_SIZE, &timex);
    Serial.print(timex.hour);
    Serial.print(":");
    Serial.println(timex.minute);

    myLCD.PCF8574_LCDClearScreen();
    myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberOne, 0);
    char txt[16];
    sprintf(txt, "%d:%d", timex.hour, timex.minute);
    myLCD.PCF8574_LCDSendString(txt);

  } else if (ans == ERROR_TIMEOUT) {
    myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberOne, 0);
    myLCD.PCF8574_LCDSendString("No sgn           ");
  } else {
    myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberOne, 0);
    myLCD.PCF8574_LCDSendString("Err.             ");
  }
}
