//https://github.com/Avamander/arduino-tvout

#include <Arduino.h>
#include <TVout.h>
#include <fontALL.h>

TVout TV;

void setup() {
  TV.begin(PAL,120,96);
  TV.select_font(font6x8);
  
  TV.println("Hello World!\n");
  TV.delay(3000);
  TV.clear_screen();
   
  //circles
  TV.clear_screen();
  TV.draw_circle(TV.hres()/2, TV.vres()/2 ,TV.vres()/3 ,WHITE);
  TV.delay(2000);  
}

void loop() {  
  TV.clear_screen();
  TV.draw_rect(20,20,20,20,WHITE);
  TV.delay(1000);
  TV.draw_rect(40,20,20,20,WHITE,INVERT);
  TV.delay(1000);
}

