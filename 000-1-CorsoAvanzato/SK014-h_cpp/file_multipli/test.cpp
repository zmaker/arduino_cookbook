#include "test.h"

int hello() {
  return 12;  
}

void sayHello(Stream *s){
  #if DEBUG > 0
  s->println("ok");
  #endif
}
