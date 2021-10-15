#include <Wire.h>

/*
 * Lib: https://github.com/DFRobot/DFRobot_MCP23017
*/
#include <DFRobot_MCP23017.h>

DFRobot_MCP23017 mcp(Wire, 0x27);

void setup() {
  Serial.begin(9600);
  while(mcp.begin()){
    Serial.println("Initialization of the chip failed, please confirm that the chip connection is correct!");
    delay(1000);
  }
  /*pinMode function is used to set the pin mode of the module
  Parameter pin, the available parameter is shown below:
  eGPA0  eGPA1  eGPA2  eGPA3  eGPA4  eGPA5  eGPA6  eGPA7  eGPA
   0       1      2      3      4      5      6      7
  eGPB0  eGPB1  eGPB2  eGPB3  eGPB4  eGPB5  eGPB6  eGPB7  eGPB
   8       9      10     11     12     13     14     15
  Parameter mode, can be set to: INPUT, OUTPUT, INPUT_PULLUP mode (internal 100KΩ pull-up resistor)
  */
  mcp.pinMode(mcp.eGPA0, OUTPUT);
  mcp.pinMode(mcp.eGPA1, INPUT);
  /*Set all Group GPIOA pins to output*/
  //mcp.pinMode(mcp.eGPA, OUTPUT);
}

void loop() {
   if (mcp.digitalRead(mcp.eGPA1)) {
     mcp.digitalWrite(mcp.eGPA0, HIGH);
   } else {
     mcp.digitalWrite(mcp.eGPA0, LOW);
   }
}
