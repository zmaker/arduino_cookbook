#include <Nextion.h>

NexButton bOn = NexButton(0, 3, "b0");
NexButton bOff = NexButton(0, 4, "b1");

NexTouch *nex_listen_list[] = {
  &bOn, &bOff, NULL
};

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  nexInit();
  bOn.attachPop(bton, &bOn);
  bOff.attachPop(btoff, &bOff);

}

void loop() {
  nexLoop(nex_listen_list);
}

void bton(void *ptr) {
  digitalWrite(13, HIGH);  
}

void btoff(void *ptr) {
  digitalWrite(13, LOW);  
}
