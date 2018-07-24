/*
Lettura dei codici di un telecomando
 */
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(13, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    if (results.value == 0x20DF8877) {
      digitalWrite(13, HIGH);
    }
    if (results.value == 0x20DF48B7) {
      digitalWrite(13, LOW);
    }
  }
  delay(100);
}
