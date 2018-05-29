int seq[10];

void setup()
{  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  //inizializzo i numeri casuali
  randomSeed(analogRead(0));
  
  //genero la sequenza di numeri casuali tra 1 e 4
  for (int i = 0; i < sizeof(seq); i++)
  {
    seq[i] = random(10,14);
    delay(50);
  }
  
  //accendo i led leggendo la sequnza generata
  for (int i = 0; i < sizeof(seq); i++)
  {
    digitalWrite(seq[i], HIGH);
    delay(300);
    
    //spengo tutti i led
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    
  }
}

void loop()
{
   
}
