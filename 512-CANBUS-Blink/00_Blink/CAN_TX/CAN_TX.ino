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

char statoled = 0;
//unsigned char data[8] = {'D', 'F', 'R', 'O', 'B', 'O', 'T', '!'};
unsigned char data[1] = {'A'};
int c = 0;

void loop() {
  // send data:  id = 0x06, standrad flame, data len = 8, data: data buf
  if (c%2 == 0) data[0] = 'A';
  else data[0] = 'S';
  
  CAN.sendMsgBuf(0x01, 0, 1, data);
  delay(500);                       // send data per 100ms
  c++;
}
  
