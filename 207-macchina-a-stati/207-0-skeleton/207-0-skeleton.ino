int stato = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  switch (stato) {
    case 0:
      loop0();
    break; 
    case 1:
      loop1();
    break; 
    case 2:
      loop2();
    break; 
    case 3:
      loop3();
    break; 
  }
}

void loop0() {}
void loop1() {}
void loop2() {}
void loop3() {}


