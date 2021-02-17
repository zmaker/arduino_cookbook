#include <genieArduino.h>
#include <SoftwareSerial.h>

/***
 * Le lib e le ref in c: https://github.com/4dsystems/ViSi-Genie-Arduino-Library
 * 
 * http://docshare04.docshare.tips/files/25589/255892337.pdf
 */

SoftwareSerial sserial(2, 3); // RX, TX

Genie genie;
#define RESETLINE 4 

void setup() {
  Serial.begin(9600);
  
  sserial.begin(9600); 
  genie.Begin(sserial);

  genie.AttachEventHandler(myGenieEventHandler); // Attach the user function Event Handler for processing events

  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, LOW);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, HIGH);  // unReset the Display via D4

  delay (3000); 

  // Set the brightness/Contrast of the Display - (Not needed but illustrates how)
  // Most Displays use 0-15 for Brightness Control, where 0 = Display OFF, though to 15 = Max Brightness ON.
  // Some displays are more basic, 1 (or higher) = Display ON, 0 = Display OFF.  
  genie.WriteContrast(10); // About 2/3 Max Brightness
}

void loop() {
  genie.DoEvents(); // This calls the library each loop to process the queued responses from the display
}

void myGenieEventHandler(void) {
  genieFrame Event;
  genie.DequeueEvent(&Event); // Remove the next queued event from the buffer, and process it below

  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) {
    if (Event.reportObject.object == GENIE_OBJ_4DBUTTON){
      if (Event.reportObject.index == 2) {
        genie.WriteObject(GENIE_OBJ_FORM, 0x01, 0);
      }
    }
  }
}
