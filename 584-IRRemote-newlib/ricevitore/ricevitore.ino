#include <IRremote.h>  // use the library 

//#define DECODE_HASH   

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("ok");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long keycode = IrReceiver.decodedIRData.command;
    Serial.println(keycode);
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
         IrReceiver.resume();
         return;
    }
    IrReceiver.resume();
  }
}
