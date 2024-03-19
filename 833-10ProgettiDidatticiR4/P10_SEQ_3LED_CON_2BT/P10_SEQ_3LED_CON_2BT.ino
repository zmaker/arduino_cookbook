/* #10 - shift dei led con 2 BT

 - LED su D5, D6, D7
 - BUTTON su D2 e D3

uso i BT per spostare il LED attivo
*/

//pin del LED
int led[3]= {5,6,7};

//pin del pulsante
int bt1 = 2;
int bt2 = 3;

//indice led corrente
int led_corrente = 0;

void setup() {
  //imposto i pin
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
  }
  //imposto i led
  setled();
}

void loop() {
  //se il tasto 1 viene premuto...
  if (digitalRead(bt2)) {
    //cambio lo stato
    led_corrente++;
    //faccio ciclare lo stato
    if (led_corrente > 2) led_corrente = 2;
    //imposta i led
    setled();
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }
  //se il tasto 2 viene premuto...
  if (digitalRead(bt1)) {
    //cambio lo stato
    led_corrente--;
    //faccio ciclare lo stato
    if (led_corrente < 0) led_corrente = 0;
    //imposta i led
    setled();
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }
}

void setled() {
  //li spengo tutti
  for (int i = 0; i < 3; i++) {
    digitalWrite(led[i], LOW);
  }
  //accendo quello attivo
  digitalWrite(led[led_corrente], HIGH);
}
