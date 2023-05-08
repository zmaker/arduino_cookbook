// https://sourceforge.net/projects/dmxlibraryforar/
#include <Conceptinetics.h>

DMX_Master dmx_master(4, 2);

void setup() {
  dmx_master.enable();
}

int ch = 1;

void loop() {
  //dmx_master.setChannelRange(ch1, ch2, i);
  for (int i = 0; i <= 255; i++) {
    dmx_master.setChannelValue(ch, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    dmx_master.setChannelValue(ch, i);
    delay(10);
  }
  ch++;
  if (ch >= 4) ch = 1;
  
}
