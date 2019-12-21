void setup() {
  pinMode(13, OUTPUT);
}

unsigned long t1, dt;
int LED = LOW;
int tempo = 100;

void loop() {
  
  dt = millis() - t1;
  if (dt >= tempo) {
    t1 = millis();
    LED = !LED;
    digitalWrite(13, LED);

    if (LED) {
      tempo = 100;  
    } else {
      tempo = 1000;
    }
  }

}

void rst() {
  asm volatile (" jmp 0");  
}
