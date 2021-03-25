// https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_#target_4
// demo: CAN-BUS Shield, send data
#include <df_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCPCAN CAN(SPI_CS_PIN);
 
void setup() {
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

unsigned long t1, dt;
//RICEZIONE
unsigned char len = 0;
unsigned char buf[8];
unsigned int remoteval;

unsigned int canid;

void loop() {
  //RICEZIONE
  if (CAN_MSGAVAIL == CAN.checkReceive()){        
    CAN.readMsgBuf(&len, buf);
    canid = CAN.getCanId();
        
    if (canid == 0x10) { //joy
      //leggo il valore
      remoteval = (byte)buf[1];
      remoteval = remoteval << 8;
      remoteval |= (byte)buf[0];
      Serial.print("rem=");Serial.println(remoteval);

      //adatto il valore
      unsigned int val = map(remoteval, 0, 1024, 0, 180);
      //trasmetto
      Serial.print("val=");Serial.println(val);
      buf[0] = (char)(val);      
      CAN.sendMsgBuf(0x02, 0, 1, buf);          
    }   
  }
}
  
