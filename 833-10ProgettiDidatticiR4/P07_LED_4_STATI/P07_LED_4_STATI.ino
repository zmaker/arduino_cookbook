/* #7 - lampada a LED con 4 stati

 - LED su D5
 - BUTTON su D2

 STATI: OFF, ON e BLINK
*/

//pin del LED
int led = 5;

//pin del pulsante
int bt = 2;

//stato per il led
int stato = 0;

//variabile per il timer del blink
unsigned long t1;

void setup() {
  //imposto i pin
  pinMode(bt, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //se il tasto 1 viene premuto...
  if (digitalRead(bt)) {
    //cambio lo stato
    stato++;
    //faccio ciclare lo stato
    if (stato > 2) stato = 0;
    Serial.println(stato);
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);

  }

  switch(stato) {
    case 0:
      ledoff();
      break;
    case 1:
      ledfull();
      //salvo il tempo corrente in t1 (serve se poi passo a blink!)
      t1 = millis();
      break;
    case 2:
      ledblink();
      break;
  }
}

void ledoff(){
  //spengo il led
  digitalWrite(led, LOW);
}

void ledfull(){
  //accendo il led
  digitalWrite(led, HIGH);
}

void ledblink(){
  //NB Blink
  if ((millis()-t1) > 500) {
    digitalWrite(led, !digitalRead(led));
    t1 = millis();
  } 
}
