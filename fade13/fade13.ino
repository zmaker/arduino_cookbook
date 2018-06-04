void setup() {  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

int MAX = 100;
int i = 1;  //lunghezza accensione/spegnimento
int c = 0; //contatore
int sgn = 1;

void loop() {
  //il contatore cresce
  c++;
  
  digitalWrite(13, HIGH);   
  delayMicroseconds(i);     
  digitalWrite(13, LOW);    
  delayMicroseconds(MAX - i);   

  //ogni 5 passi del contatore incremento la pausa di sgn 
  //che può valere 1 o -1
  if ((c%5) == 0) i = i + sgn;

  //arrivato con la pausa a 100 usec, inverto il segno
  if (i >= 100) {
    sgn = -1;
  }
  if (i <= 0) {
    sgn = 1;
    i = 1;
  }
  Serial.println(i);
}
