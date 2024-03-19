/* #9 - Contrrollo luminosità per 3 LED (es RGB)

 - LED su D3, D5, D6
 - BUTTON su D2
 - POT su A0

uso il BT per selezionare il LED e monidificare la luminosità
*/

//pin del LED
int led[3]= {3,5,6};

//pin del pulsante
int bt = 2;

//indice led corrente
int led_corrente = 0;

//luminosità led
int lumi[3] = {0,0,0};

void setup() {
  //imposto i pin
  pinMode(bt, INPUT);
}

void loop() {
  //se il tasto 1 viene premuto...
  if (digitalRead(bt)) {
    //cambio lo stato
    led_corrente++;
    //faccio ciclare lo stato
    if (led_corrente > 2) led_corrente = 0;
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }

  //per il LED corrente leggo l'intensità
  int val = analogRead(A0);
  //la salvo nell'array
  lumi[led_corrente] = val;
  //la applico
  analogWrite(led[led_corrente], lumi[led_corrente]);
}
