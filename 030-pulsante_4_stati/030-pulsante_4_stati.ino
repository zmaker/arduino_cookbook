//lo stato contiene il numero del pin da accendere
//il pin 9 non è collegato e corrisponde al caso in cui tutti
//i led sono spenti
int stato = 9;

void setup()
{  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(2, INPUT);
}

void loop()
{
  if (digitalRead(2) == HIGH) 
  {
  	stato++;
    if (stato > 13)
    {
      stato = 9;
    }
    delay(200);
  }
  
  //spengo tutti i led
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  //accendo il led selezionato
  digitalWrite(stato, HIGH);
}