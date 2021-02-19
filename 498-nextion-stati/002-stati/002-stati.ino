/**
 * REF: https://github.com/itead/ITEADLIB_Arduino_Nextion
 */
#include "Nextion.h"

NexPage page0 = NexPage(0, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");
NexPage page2 = NexPage(2, 0, "page2");

NexCheckbox chk1 = NexCheckbox(0, 2, "c0");
long checkbox_state = 0;
NexSlider sli1 = NexSlider(1, 1, "h0");
long slider_pos = 0;
NexNumber num1 = NexNumber(2, 1, "n0");
long count = 0;

NexTouch *nex_listen_list[] = {
  &chk1, &sli1, NULL
   
};

void setup() {
  nexInit();
  chk1.attachPop(evh_checkbox, &chk1);
  sli1.attachPop(evh_slider, &sli1);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  delay(1000);
  
  chk1.setValue(checkbox_state);
  page0.show();
}

int stato = 0;

void loop() {
  nexLoop(nex_listen_list);
  switch(stato){
    case 0:
      showPage0();
      break;
    case 1:
      showPage1();
      break;
    case 2:
      showPage2();
      break;
   }
}

void evh_checkbox(void *ptr) {
  chk1.getValue(&checkbox_state);
}

void evh_slider(void *ptr) {
  sli1.getValue(&slider_pos);
}

bool FIRST = true;

void go(int n) {
  delay(300);
  stato = n;
  FIRST = true;   
}

void showPage0(){
  if (FIRST){
    chk1.setValue(checkbox_state);
    FIRST = false;
  }
  if (digitalRead(3)) {
    page1.show();
    go(1);  
  }
}
void showPage1(){
  if (FIRST){
    sli1.setValue(slider_pos);
    FIRST = false;
  }
  if (digitalRead(2)) {
    page0.show();
    go(0);  
  }
  if (digitalRead(3)) {
    page2.show();
    go(2);  
  }
}
void showPage2(){
  if (FIRST){
    num1.setValue(count);
    count++;
    FIRST = false;
  } 
  if (digitalRead(2)) {
    page1.show();
    go(1);  
  } 
}
