/**
 * https://github.com/Arduino-IRremote/Arduino-IRremote
 */
#include <IRremote.h> 
#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("ok");
}


void loop() {
  int ircode = readIr();
  if (ircode != 0) {
    Serial.print("code: ");
    Serial.println(ircode);
  }
}


int readIr() {
  int code = 0;
  if (IrReceiver.decode()) {
    code = IrReceiver.decodedIRData.command;
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
         IrReceiver.resume();
         return;
    }
    IrReceiver.resume();
  }  
  return code;
}
