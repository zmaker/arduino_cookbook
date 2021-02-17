#include <genieArduino.h>
#include <SoftwareSerial.h>

/***
 * Le lib e le ref in c: https://github.com/4dsystems/ViSi-Genie-Arduino-Library
 */

SoftwareSerial sserial(2, 3); 
Genie genie;

unsigned long t1, dt;

void setup() {
  sserial.begin(9600);
  genie.Begin(sserial);

  genie.AttachEventHandler(myGenieEventHandler);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(3000);

  genie.WriteContrast(10);

  pinMode(11, OUTPUT);
}

void loop() {
  genie.DoEvents();  
}

void myGenieEventHandler() {
  genieFrame Event;
  genie.DequeueEvent(&Event);
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER) {
      if (Event.reportObject.index == 0) {
        int n = genie.GetEventData(&Event);
        analogWrite(11, map(n, 0, 100, 0, 255));
        genie.WriteObject(GENIE_OBJ_METER, 0, n);
      }
    } 
  }
}
