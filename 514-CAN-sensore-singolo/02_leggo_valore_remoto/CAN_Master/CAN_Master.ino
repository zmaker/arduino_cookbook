// https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_#target_4
// demo: CAN-BUS Shield, send data
  #include <df_can.h>
  #include <SPI.h>

  const int SPI_CS_PIN = 10;
  MCPCAN CAN(SPI_CS_PIN);
  
//display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);  
  lcd.home();    
  lcd.print("CAN Bus test");    
  
  Serial.begin(9600);    
  CAN.init();
  CAN.init_Mask(MCP_RXM0, 0, 0x3ff); 
  CAN.init_Mask(MCP_RXM1, 0, 0x3ff);    
  CAN.init_Filter(MCP_RXF0, 0, 0x10); //risponbde all'id=0x10
  
  if(CAN_OK != CAN.begin(CAN_500KBPS)){
     Serial.println("CAN KO");
     abort();
  }    
}

unsigned char cmd[1] = {0};
unsigned long t1, dt;
//RICEZIONE
unsigned char len = 0;
unsigned char buf[8];
unsigned int remoteval;

void loop() {

  dt = millis() - t1;
  if (dt >= 200) {
    cmd[0] = 'T';  //chiedo la temp
    CAN.sendMsgBuf(0x02, 0, 1, cmd);
    //richiedo un secondo dato
    //cmd[0] = 'L';
    //CAN.sendMsgBuf(0x03, 0, 1, cmd);
    
    t1 = millis();
  }

  //RICEZIONE
  if (CAN_MSGAVAIL == CAN.checkReceive()){        
    CAN.readMsgBuf(&len, buf);
    remoteval = (byte)buf[1];
    remoteval = remoteval << 8;
    remoteval |= (byte)buf[0];
    Serial.print("val=");Serial.println(remoteval);

    lcd.setCursor(0,1);
    lcd.print("luce: ");
    lcd.print(remoteval);
  }
}
  
