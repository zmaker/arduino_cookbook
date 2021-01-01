#include <TimerOne.h>
#include <MultiFuncShield.h>

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);

  MFS.write("Hi");
  delay(2000);
  MFS.write(-273);
  delay(2000);
  MFS.write(3.141, 2);  // display to 2 decimal places.
  delay(2000);
}

int counter = 0;

void loop() {
  if (counter < 100) {
    MFS.write((int)counter);
    counter++; 
  } else {         
    MFS.write("End");
    MFS.blinkDisplay(DIGIT_ALL, ON);
    delay(2000);
    counter = 0;
  }
  delay(50);
}
