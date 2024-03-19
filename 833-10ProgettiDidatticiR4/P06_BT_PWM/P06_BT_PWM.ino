/* #6 - LED in PWM con intensità controllata da due bt

 - LED su D5
 - BUTTON su D2, D3
*/

//pin del LED
int led = 5;

//pin dei pulsanti
int bt1 = 2;
int bt2 = 3;

//livello di luminosità
int lumi = 0;

void setup() {
  //imposto i pin
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
}

void loop() {
  //se il tasto 1 viene premuto...
  if (digitalRead(bt1)) {
    //incremento luminosità
    lumi += 10;
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }

  //se il tasto 2 viene premuto...
  if (digitalRead(bt2)) {
    //diminuisco luminosità
    lumi -= 10;
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }

  //limito i valori tra 0 e 100
  lumi = constrain(lumi, 0, 100);

  //calcolo il pwm
  int pwm = map(lumi, 0, 100, 0, 255);
  //modifico il pwm sul pin
  analogWrite(led, pwm);
}
