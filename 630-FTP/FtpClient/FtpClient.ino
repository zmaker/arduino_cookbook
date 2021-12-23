/*
  Web client
  ENC28j60
  https://playground.arduino.cc/Code/FTP/
 */

#include <SPI.h>
//#include <Ethernet.h>
#include <UIPEthernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 112);
IPAddress myDns(192, 168, 1, 1);

// Initialize the Ethernet client library
EthernetClient client;
EthernetClient dclient;

//FTP:
IPAddress server( 192, 168, 1, 198 );
//char server[] = "ftp.server.it";  
char user[] = "java";
char pasw[] = "java";
char fold[] = "download";
char fname[] = "dati.txt";

char outBuf[128];
byte outCount;

void setup() {
  Ethernet.init(10);  // Most Arduino shields
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }  
  
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  Ethernet.begin(mac);
  Serial.print("Assigned IP: ");
  Serial.println(Ethernet.localIP());
  
  
  
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'f') doFTP();  
  }
}

byte doFTP() {
  if (client.connect(server,21)) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }

  if(!eRcv()) return 0;

  client.print(F("USER "));
  client.println(user);

  if(!eRcv()) return 0;

  client.print(F("PASS "));
  client.println(pasw);

  if(!eRcv()) return 0;

  client.println(F("SYST"));

  if(!eRcv()) return 0;

  client.println(F("Type I"));

  if(!eRcv()) return 0;

  client.println(F("PASV"));

  if(!eRcv()) return 0;

  char *tStr = strtok(outBuf,"(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL,"(,");
    array_pasv[i] = atoi(tStr);
    if(tStr == NULL)
    {
      Serial.println(F("Bad PASV Answer"));    

    }
  }

  client.println(F("PWD"));
  if(!eRcv()) return 0;

  client.print(F("CWD "));
  client.println(fold);
  if(!eRcv()) return 0;


  unsigned int hiPort,loPort;

  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  Serial.print(F("Data port: "));
  hiPort = hiPort | loPort;
  Serial.println(hiPort);

  if (dclient.connect(server,hiPort)) {
    Serial.println(F("Data connected"));
  } else {
    Serial.println(F("Data connection failed"));
    client.stop();
    return 0;
  }

  client.print(F("STOR "));
  client.println(fname);

  if(!eRcv()) {
    dclient.stop();
    return 0;
  }

  Serial.println(F("Writing"));
  char dati[10];
  sprintf(dati, "A0: %d\n", analogRead(A0));

  byte clientBuf[64];
  int clientCount = 0;

  dclient.write(dati,sizeof(dati));
 
  dclient.stop();
  Serial.println(F("Data disconnected"));

  if(!eRcv()) return 0;

  client.println(F("QUIT"));

  if(!eRcv()) return 0;

  client.stop();
  Serial.println(F("Command disconnected"));

  return 1;
}

byte eRcv() {
  byte respCode;
  byte b;

  while(!client.available()) delay(1);
  respCode = client.peek();
  outCount = 0;
  while(client.available()) {  
    b = client.read();    
    Serial.write(b); 
    if(outCount < 127) {
      outBuf[outCount] = b;
      outCount++;      
      outBuf[outCount] = 0;
    }
  }

  if(respCode >= '4') {
    ftperror();
    return 0;  
  }

  return 1;
}

void ftperror() {
  byte b = 0;
  client.println(F("QUIT"));
  while(!client.available()) delay(1);
  while(client.available()) {  
    b = client.read();    
    Serial.write(b);
  }

  client.stop();
  Serial.println(F("disconnected"));  
}
