// https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_#target_4
// demo: CAN-BUS Shield, send data
  #include <df_can.h>
  #include <SPI.h>

  const int SPI_CS_PIN = 10;
  MCPCAN CAN(SPI_CS_PIN);

  void setup() {
    Serial.begin(9600);    
    CAN.init();
    if(CAN_OK != CAN.begin(CAN_500KBPS)){
       Serial.println("CAN KO");
       abort();
    }    
}

unsigned char data[2] = {0,0};
unsigned int x = 0x01FF; //511

void loop() {
  //To send a remote request, OR the ID with 0x40000000.
  //(0x02|0x40000000) remoto... ma non va
  data[0] = (char)(x & 0x00FF);
  data[1] = (char)((x & 0xFF00) >> 8);
  CAN.sendMsgBuf(0x02, 0, 2, data);
  //richiedo un secondo dato
  //data[1] = 'L';
  //CAN.sendMsgBuf(0x03, 0, 1, data);


  delay(1000);
  
}
  
