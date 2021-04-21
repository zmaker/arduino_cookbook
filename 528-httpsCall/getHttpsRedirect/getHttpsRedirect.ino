#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID; 
char pass[] = SECRET_PASS; 
//int keyIndex = 0;          

int status = WL_IDLE_STATUS;
char server[40] = "script.google.com";   
String path = "/macros/s/AKfycbymzr_fSZhNUjqvEqK3aLTyXXaO9cHnj7_9jTsnf5O8m9dkiJRZhSVBuRgNWt3XEwFFng/exec";

WiFiSSLClient client;

void setup() {  
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!\nSTOPPED");    
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);    
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to wifi");
}

int stato = 0;

void loop() {
  switch(stato){
    case 0:
      //attendo comando da seriale
      waitcmd();     
      break;
    case 1:
      //chiamo l'indirizzo
      call();
      break;
    case 2:
      //leggo il codice della risposta e decido come rpocedere (200, 302, 404, 500...)
      getHeader();
      break;
    case 3:
      //leggo dati
      readdata();
      break;
  }
}

boolean FIRST = true;
void go(int st){
  stato = st;
  FIRST = true;
  delay(300);
}

void waitcmd() {
  if (FIRST) {
    Serial.println("Attendo avvio...");
    FIRST = false;
  }
  while (Serial.available()){
    char c = Serial.read();
    Serial.print(c);
    if (c == '\n') {      
      go(1);  
    }
  }
}

void call() {
  if (FIRST) {
    Serial.println("Chiamata...");
    Serial.print(server);
    Serial.println(path);    
    FIRST = false;
  }
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET "+path+" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
    go(2);
  }
}

int requestCode;

void getHeader() {
  if (FIRST) {
    Serial.println("Analisi Header...");    
    FIRST = false;
  }

  if (client.available()) {
    String line = client.readStringUntil('\n');
    //Serial.println(line);     
    
    if (line.indexOf("HTTP/1.1") >= 0) {   
      requestCode = getRequestCode(line);
      
    } else if ((requestCode == 302) && (line.indexOf("Location:") >= 0)) {
      int pos = line.indexOf(" ");
      String newaddr = line.substring(pos+1);
      Serial.println("--------");
      Serial.println(newaddr);
      int s = line.indexOf("//")+2;
      int f = line.indexOf("/", s) + 1;
      String str = line.substring(s, f);
      str.toCharArray(server, str.length());
      Serial.print("server="); Serial.println(server);      
      path = line.substring(f-1);
      Serial.print("path="); Serial.println(path);      
      
    } else if (line.indexOf("Connection: close") >= 0){
      Serial.println("decide che fare...");
      if (requestCode == 302) {
        //redirect  
        client.flush();
        go(1);
      } else if (requestCode == 200){
        //leggo i dati  
        go(3);
      } else {
        //non gestito
        client.flush();
      }
    }
  }
}

int getRequestCode(String line) {
  int n = 0;
  char ll[100] = ""; 
    line.toCharArray(ll, line.length());
    int i = 0;
    char* token = strtok(ll, " ");
    while (token != NULL) {
        i++;        
        token = strtok(NULL, " ");
        if (i == 1) {  //qui ho il codice della risposta
          n = atoi(token);
        }        
    }  
    return n;
}

int linea;
void readdata(){
  if (FIRST) {    
    Serial.println("Lettura dati");    
    FIRST = false;
    linea = 0;
  }
  if (client.available()) {
    String line = client.readStringUntil('\n');
    if (linea == 3) {
      Serial.println(line);      
      go(0);
    }    
    linea++; 
  }
}
