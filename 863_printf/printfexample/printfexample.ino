#include <LibPrintf.h>

int v = 123;

void setup() {
  Serial.begin(9600);
  printf("Hello printf!\n");
  printf("v: %d\n", v);
  printf("v: %f\n", 123.45);

  printf("%5d %5d %5d\n", 12, 23, 456);
  printf("%05d %05d %05d\n", 12, 23, 456);
  printf("v: %d %%\n", v);

  printf("%*.*f\n", 10,3, 123.45678);

  printf("msg: %s \n", "ciao");
  printf("char: %c \n", 'a');

  printf("addr: %02X %02X \n", 12, 129);
}

void loop() {
  // put your main code here, to run repeatedly:

}
