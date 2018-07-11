void setup() {
  Serial.begin(9600);
  Serial.println("setup...");
}

int c = 0;

void loop() {
  if (c == 5){
    Serial.println("reset!");
    delay(1000);
    //pausa di 62 nanosecondi (la più breve possibile!)
    asm volatile (" nop ");  
    //reset!
    asm volatile (" jmp 0 ");  
  }
  c++;
  delay(1000);
}
