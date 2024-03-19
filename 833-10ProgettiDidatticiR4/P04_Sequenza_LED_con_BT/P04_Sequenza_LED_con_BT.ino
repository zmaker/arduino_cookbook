/* #4 - Sequenza di LED con pulsante

Versione semplice senza debouncing o rilevazione 
dei fronti di salita o discesa. 
Utilizza una semplice delay

 - LED su D5, D6 e D7
 - BUTTON su D2
*/

//pin del LED
int led1 = 5;
int led2 = 6;
int led3 = 7;

//pin del pulsante
int bt = 2;

//stato = che LED accendo?
int stato = 0;

void setup() {
  //imposto i pin
  pinMode(bt, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  //se il tasto viene premuto
  if (digitalRead(bt)) {
    //cambio lo stato
    stato++;
    //se stato > 2, lo azzero
    if (stato > 2) stato = 0;
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(500);
  }  
  //con uno switch decido che LED accendere
  switch(stato){
    case 0:
      digitalWrite(led3, LOW);
      digitalWrite(led1, HIGH);
      break;
    case 1:
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      break;
    case 2:
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      break;
  }
}
