#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(7, 6, 0);  // Clock pin, Data pin, Orientation

void setup(){  
  bar.begin();

  bar.setBits(0B000001000000000);
  delay(1000);
  bar.setBits(0B000001100000000);
  delay(1000);
  bar.setBits(0B000000000000001);
  delay(1000);  

  bar.setLevel(0);
  delay(1000);
}

void loop() {
  int mask = 1;
  for (int i = 0; i < 10; i++) {
    bar.setBits(mask << i);
    delay(100);
  }

  delay(1000);
  bar.setLevel(0);
  delay(1000);
  
  for (int i = 9; i >= 0; i--) {
    bar.setLed(i, 1);
    delay(100);
    bar.setLed(i, 0);
    delay(100);
  }  
  delay(1000);
  bar.setLevel(0);
  delay(1000);
  
  for (int i = 0; i <= 10; i++) {
    bar.setLevel(i); 
    delay(100);
  }
  
  delay(1000);
  bar.setLevel(0);
  delay(1000);

  bar.setGreenToRed(1);
  for (int i = 0; i <= 10; i++) {
    bar.setLevel(i); 
    delay(100);
  }
  bar.setGreenToRed(0);
  for (int i = 0; i <= 10; i++) {
    bar.setLevel(i); 
    delay(100);
  }

  delay(1000);
  bar.setLevel(0);
  delay(1000);
}
