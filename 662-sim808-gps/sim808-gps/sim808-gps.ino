//REF: https://m2msupport.net/m2msupport/athttpaction-perform-getposthead-http-action/
#include <SoftwareSerial.h>

//MODEM
#define SER_TX 2
#define SER_RX 3
SoftwareSerial modem(SER_RX, SER_TX);

unsigned long t1;

int resp (String txt = "OK");
void sendCommand(Stream *ser, String cmd, String ans = "OK", int tryon = 3);
String getGPSData(Stream *ser);

struct gpsstruct {
  float lat;
  float lon;
  float alt;
} location;

void setup() {
  Serial.begin(9600);
  //il modem deve inizializzarsi
  for (int i = 0; i < 5; i++) {
    delay(100);
    Serial.print(".");
  }
  modem.begin(9600);
  Serial.println("\nOK:");

  int n = 0;
  sendCommand(&modem, "AT");
  
  //prendere info GPS
  sendCommand(&modem, "AT+CGNSPWR=1");  
  String data = getGPSData(&modem);
  Serial.print("GPS: ");Serial.println(data);
  processGPSData(data, &location);

  //esempi:
  /*
  processGPSData("+CGNSINF: 0,,,,,,,,,,,,,,,,,,,,", &location);
  processGPSData("+CGNSINF: 1,0,20220407092626.000,,,,0.17,198.8,0,,,,,,5,3,,,40,,", &location);
  processGPSData("+CGNSINF: 1,1,20220407092629.000,45.311292,9.357338,101.900,0.76,126.9,1,,4.1,4.2,1.0,,5,3,,,34,,", &location);
  Serial.print("lat:");Serial.println(location.lat);
  Serial.print("lon:");Serial.println(location.lon);
  Serial.print("alt:");Serial.println(location.alt);
  */
  
  t1 = millis();
}

void loop() {    
  if (modem.available()) {
      char c = modem.read();
      Serial.write(c);
  }
  if (Serial.available()) {
      char c = Serial.read();
      modem.write(c);
  }

  if ((millis() - t1) > 5000) {
    String data = getGPSData(&modem);
    Serial.print("GPS: ");Serial.println(data);
    processGPSData(data, &location);

    t1 = millis();
  }
}

void sendCommand(Stream *ser, String cmd, String ans = "OK", int tryon = 3){  
  int n = 0;
  int tentativi = 0;
  do {
    delay(1000);
    Serial.print("\nSEND: ");Serial.println(cmd);
    ser->println(cmd);      
    n = resp(ans);   
    Serial.print("\nRET : ");Serial.println(n); 
    tentativi++;
  } while ((n < 0) && (tentativi <  tryon));   
}

String getGPSData(Stream *ser) {
  String line = "";
  String page = "";
  bool LOOP = true;
  int n = 0;
  ser->println("AT+CGNSINF");
  while(LOOP) {
    if (ser->available()) {
      char c = ser->read();      
      //Serial.write(c);          
      if (c == '\n') {
        //Serial.println(line);
        int d = line.indexOf("+CGNSINF:");  
        if (d >= 0) {
          page = line;
        }
        //attendo OK per uscire
        if (line.indexOf("OK") >= 0) LOOP = false;
                             
        line = ""; 
      } else if (c != '\r') {
        line += c;
      }  
    }
  }  
  return page;
}

int resp (String txt = "OK") {   
  int n = 0; 
  String line = "";
  int rows = 0;
  while (true) {
    if (modem.available()) {
      char c = modem.read();
      //Serial.write(c);
      if (c == '\n') {
        rows++;
        Serial.print("->|");Serial.print(line);Serial.print("|(");
        Serial.print(line.length());Serial.println(")");
        //Serial.print("rows:");Serial.println(rows);
        if (line.indexOf(txt) >= 0) {
          //Serial.print("trovato:");Serial.println(txt);
          n = 1;
          break; 
        } else if (line.equals("ERROR")) {
          n = -1;
          break; 
        }
        line = "";
      } else if (c == '\r') {        
      } else {
        line += c;                 
      } 
    }   
  }
  return n;
}

/**
 * 
 * +CGNSINF: <GNSS run status>,<Fix status>,
<UTC date & Time>,<Latitude>,<Longitude>,<MSL Altitude>,<Speed Over Ground>,
<Course Over Ground>,
<Fix Mode>,<Reserved1>,<HDOP>,<PDOP>,
<VDOP>,<Reserved2>,<GNSS Satellites in View>,
<GNSS Satellites Used>,<GLONASS Satellites
Used>,<Reserved3>,<C/N0 max>,<HPA>,<VPA>
 * 
 */

void processGPSData(String line, struct gpsstruct *location){
  if (line.length() > 0) {    
    int m = 0;
    int n = line.indexOf(",");
    int indice = 0;
    while (n > 0) {      
      String token = line.substring(n, m);
      //Serial.print("(");Serial.print(indice);Serial.print(")\t");Serial.println(token);
      m = n+1;
      n = line.indexOf(",", n+1);
      //elaboro il token:
      switch(indice) {
        case 3:
          location->lat = atof(token.c_str());          
          break;
        case 4:
          location->lon = atof(token.c_str());          
          break;
        case 5:
          location->alt = atof(token.c_str());          
          break;
      }
      indice++;
    }    
  }  
}
