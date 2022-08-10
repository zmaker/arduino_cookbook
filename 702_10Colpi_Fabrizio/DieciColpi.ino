#define COLPI_MAX 3
unsigned long TEMPO_TIMER = 2000;

int bt, pvbt;
int count = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  bt = digitalRead(2);
  
  if (bt && !pvbt) {
  	//FDS
    count++;
  }
  
  if (count == COLPI_MAX) {
   	digitalWrite(9, HIGH);
    delay(TEMPO_TIMER);
    digitalWrite(9, LOW);
    count = 0;
  }
  
  pvbt = bt;
}