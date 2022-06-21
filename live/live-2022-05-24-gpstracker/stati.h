#ifndef _STATI_H_
#define _STATI_H_

#define _SETUP_BEGIN_ if (FIRST) { 
#define _SETUP_END_ FIRST = false; }

//definizioni
void go(enum stati st);
void act_startup(Stream *out, SoftwareSerial *modem);
void act_work(Stream *out);
void act_getposition(Stream *out, SoftwareSerial *neo6, TinyGPS *gps);
void act_callservice(Stream *out, SoftwareSerial *modem);
int resp (Stream *out, SoftwareSerial *modem, String cmd, String txt, String* payload = NULL); //risposta del modem

//implementazioni
void go(enum stati st){
  stato = st; 
  FIRST = true; 
}
void act_startup(Stream *out, SoftwareSerial *modem){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("startup");
    modem->listen();
  _SETUP_END_ 

  int n = 0;
  n = resp(out, modem, "AT", "OK");
  out->print("modem resp: ");out->println(n);

  //la sim è pronta
  n = resp(out, modem, "AT+CPIN?", "OK");
  out->print("modem resp: ");out->println(n);

  String risposta = "";
  do {
    delay(4000);
    n = resp(out, modem, "AT+CREG?", "OK", &risposta);
    out->print("modem resp: ");out->println(n);
    out->print("risposta: ");out->println(risposta);    
  } while ((risposta != "+CREG: 0,1") && (risposta != "+CREG: 0,5"));
  /*
0 – Not registered, the device is currently not searching for new operator.
1 – Registered to home network.
2 – Not registered, but the device is currently searching for a new operator.
3 – Registration denied.
4 – Unknown. For example, out of range.
5 – Registered, roaming. The device is registered on a foreign (national or international) network.
   */
  n = resp(out, modem, "AT+CGATT1", "OK");
  out->print("modem resp: ");out->println(n);

  n = resp(out, modem, "AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK");
  out->print("modem resp: ");out->println(n);

  n = resp(out, modem, "AT+SAPBR=3,1,\"APN\",\""+APN+"\"", "OK");
  out->print("modem resp: ");out->println(n);
  
  go(work);
}

void act_work(Stream *out){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("work");
    t1 = millis();
  _SETUP_END_ 
  
  //codice da ripetere nello stato
  if ((millis() - t1) > TIMEOUT_SENSORE) {
    //leggo i dati e procedo all'invio     
    go(getposition); 
  }
}

void act_getposition(Stream *out, SoftwareSerial *neo6, TinyGPS *gps){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("getposition");
    neo6->listen();
  _SETUP_END_ 
  
  //codice da ripetere nello stato

  while (neo6->available()) {
    char c = neo6->read();
    out->write(c);
    if (gps->encode(c)) {
      //se ci sono dati (valido o no)
      unsigned long age;
      float lat, lon;
      gps->f_get_position(&lat, &lon, &age);
      lat = (lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat);
      lon = (lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon);
      
      out->print("lat:");out->println(lat);
      out->print("lon:");out->println(lon);
      position.lat = lat;
      position.lon = lon;
      //position.alt = 100.1;
    }
  }

  position.lat = 45.5637;
  position.lon = 9.67453;
  position.alt = 100.1;
  delay(2000);
  go(callservice);
}

void act_callservice(Stream *out, SoftwareSerial *modem){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("call service");
    modem->listen();
  _SETUP_END_ 
  
  out->println("Open GPRS bearer");
  int n = resp(out, modem, "AT+SAPBR=1,1", "OK");
  out->print("modem resp:");out->println(n);

  if (n > 0) {
    n = resp(out, modem, "AT+HTTPINIT", "OK");
    out->print("modem resp:");out->println(n);
    delay(1000);
      
    n = resp(out, modem, "AT+HTTPPARA=\"CID\",1", "OK");
    out->print("modem resp:");out->println(n);

    n = resp(out, modem, "AT+HTTPPARA=\"REDIR\",1", "OK");
    out->print("modem resp:");out->println(n);
    
    n = resp(out, modem, "AT+HTTPPARA=\"URL\",\""+url+"\"", "OK");
    out->print("modem resp:");out->println(n);
    
    n = resp(out, modem, "AT+HTTPACTION=0", "OK");
    out->print("modem resp:");out->println(n);
  
    delay(5000);
  
    //Read the HTTP result
    n = resp(out, modem, "AT+HTTPREAD", "OK");
    out->print("modem resp:");out->println(n);
    
    n = resp(out, modem, "AT+HTTPTERM", "OK");
    out->print("modem resp:");out->println(n);   
  }

  out->println("Close GPRS bearer");
  n = resp(out, modem, "AT+SAPBR=0,1", "OK");
  out->print("modem resp:");out->println(n);
  
  go(work);
}

int resp (Stream *out, SoftwareSerial *modem, String cmd, String txt, String *payload) {   
  int n = 0; 
  String line = "";
  bool LOOP = true;
  out->print("send: ");out->println(cmd);
  modem->println(cmd);
  delay(500);
  unsigned long t1 = millis();
  
  while(true){
    if ((millis() - t1) > 30000l) {
      return -2;  
    }
    
    if (modem->available()) {
      char c = modem->read();      
      //out->write(c);
      if (c == '\n') {  
        out->print("line: ");out->println(line);                
        if (line.equals(txt)) {
          out->println("trovato "+txt);
          return 1;                  
        } else if (line.indexOf("ERROR") >= 0) {
          out->println("trovato ERROR");
          return 0;
        } else if ((txt == "*") && (line.length() > 0)){
          out->println("any line ");
          return 1;
        } else if ((line.length() > 0) && (payload != NULL)) {
          *payload = line;
        }
        line = "";
      } else if (c != '\r') {       
        line += c;                 
      }    
    }
  }  
  return n;
}

#endif
