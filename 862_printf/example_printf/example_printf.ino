#include <LibPrintf.h>

void setup() {
  Serial.begin(9600);
  printf("I'm alive!\n");
  printf("x: %d \n", 100);
  printf("v: %f \n", 123.34);

  printf("%5d %5d %5d\n", 12, 23, 456);
  printf("%05d %05d %05d\n", 12, 23, 456);
  printf("%-5d %-5d %-5d\n", 12, 23, 456);
  printf("%+5d %+5d %+5d\n\n", 12, -23, 456);
  printf("%5.2f\n", 123.3456);
  printf("%10.2e\n\n", 123.3456);
  printf("str: %s\n", "ciao!");
  printf("perc: 10%%\n");

  printf("%*.*f\n", 10,3, 123.3456);

}

void loop() {
  
}