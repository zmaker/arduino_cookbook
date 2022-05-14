#include <SoftwareSerial.h>
SoftwareSerial ser(2, 3); //RX, TX

String line; 

void setup() {
  ser.begin(9600);
}

void loop() {  
  if (ser.available())  {
    char c = ser.read();
    if (c == '\n') {
      line.toUpperCase();
      if (line == "AT") {
        delay(100);
        ser.println("OK");  
      } else if (line == "AT1") {
        ser.println("");  
        delay(100);
        ser.println("");  
        delay(100);
        ser.println("OK");  
      } else if (line == "AT2") {
        ser.println("");  
        delay(100);
        ser.println("");  
        delay(100);
        ser.println("PAGE: OK");  
      } else if (line == "AT3") {
        delay(1000);
        ser.println("ERROR");  
      } else if (line == "AT4") {
        delay(1000);
        ser.println("MODEM ERROR");  
      } else if (line == "AT5") {
        delay(20000);        
      } else {
        ser.println("UNK");          
      }

      line = "";
    } else if (c != '\r') {
      line += c;
    }
  }
}
