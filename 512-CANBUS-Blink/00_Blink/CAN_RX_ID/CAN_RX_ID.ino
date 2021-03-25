// https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_#target_4
 
  // demo: CAN-BUS Shield, send data
  #include <df_can.h>
  #include <SPI.h>

  const int SPI_CS_PIN = 10;
  MCPCAN CAN(SPI_CS_PIN);

  void setup() {
    pinMode(3, OUTPUT);
    Serial.begin(9600);    
    CAN.init();    
    CAN.init_Mask(MCP_RXM0, 0, 0x3ff); // there are 2 mask in mcp2515, you need to set both of them
    CAN.init_Mask(MCP_RXM1, 0, 0x3ff);
    /*
     * set filter, we can receive id from 0x04 ~ 0x09 except for 0x06
     * // there are 6 filter in mcp2515,so it can filter six id,i.e.0x04~0x09.
     */
    CAN.init_Filter(MCP_RXF0, 0, 0x01); //risponbde all'id=1
    //CAN.init_Filter(MCP_RXF1, 0, 0x05);                         // filter 1 for id = 0x05
    // CAN.init_Filter(MCP_RXF2, 0, 0x06);                         // filter 2 for id = 0x06
    //CAN.init_Filter(MCP_RXF3, 0, 0x07);                         // filter 3 for id = 0x07
    //CAN.init_Filter(MCP_RXF4, 0, 0x08);                         // filter 4 for id = 0x08
    //CAN.init_Filter(MCP_RXF5, 0, 0x09);  
    
    if(CAN_OK != CAN.begin(CAN_500KBPS)){
       Serial.println("CAN KO");
       abort();
    }    
}

unsigned char len = 0;
unsigned char buf[8];
  
void loop(){
    
  if (CAN_MSGAVAIL == CAN.checkReceive()){
    CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf    
    for (int i = 0; i<len; i++) {
       Serial.write(buf[i]);
       Serial.print("\t");
    }
    if (buf[0] == 'A') {
      digitalWrite(3, HIGH);  
    } else {
      digitalWrite(3, LOW);
    }
    Serial.println();
  }
}
