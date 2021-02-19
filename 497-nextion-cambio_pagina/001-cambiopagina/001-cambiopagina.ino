/*
 * REF: https://github.com/itead/ITEADLIB_Arduino_Nextion
 */
#include "Nextion.h"

NexPage page1 = NexPage(0,0, "page0");
NexPage page2 = NexPage(1,0, "page1");
NexText testo1 = NexText(0,2, "t0");

void setup() {
  nexInit();
}

int c = 0;
char str[10];

void loop() {
  sprintf(str, "c: %d", c);
  testo1.setText(str);
  delay(1000);
  c++;
  page2.show();
  delay(1000);
  page1.show();
}
