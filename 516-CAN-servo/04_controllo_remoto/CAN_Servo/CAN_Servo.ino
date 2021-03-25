// https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_#target_4
 
// demo: CAN-BUS Shield, send data
#include <df_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCPCAN CAN(SPI_CS_PIN);

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(6); 
  Serial.begin(9600);    
  CAN.init();    
  CAN.init_Mask(MCP_RXM0, 0, 0x3ff); // there are 2 mask in mcp2515, you need to set both of them
  CAN.init_Mask(MCP_RXM1, 0, 0x3ff);
  /*
   * set filter, we can receive id from 0x04 ~ 0x09 except for 0x06
   * // there are 6 filter in mcp2515,so it can filter six id,i.e.0x04~0x09.
   */
  CAN.init_Filter(MCP_RXF0, 0, 0x02); //risponbde all'id=2
  
  if(CAN_OK != CAN.begin(CAN_500KBPS)){
     Serial.println("CAN KO");
     abort();
  }    
}

unsigned char len = 0;
unsigned char buf[8];
unsigned int canid;
unsigned int remoteval;
  
void loop(){
  if (CAN_MSGAVAIL == CAN.checkReceive()){        
    CAN.readMsgBuf(&len, buf);
    canid = CAN.getCanId();
        
    if (canid == 0x02) { //dal master
      //leggo il valore
      remoteval = (byte)buf[0];
      Serial.print("rem=");Serial.println(remoteval);
      myservo.write(remoteval);     
    }   
  }
}
