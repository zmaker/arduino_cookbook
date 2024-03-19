/* #5 - un bt accende e un bt spegne

 - LED su D5
 - BUTTON su D2, D3
*/

//pin del LED
int led = 5;

//pin dei pulsanti
int bt1 = 2;
int bt2 = 3;

void setup() {
  //imposto i pin
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //se il tasto 1 viene premuto...
  if (digitalRead(bt1)) {
    //accendo
    digitalWrite(led, HIGH);
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }

  //se il tasto 2 viene premuto...
  if (digitalRead(bt2)) {
    //spengo
    digitalWrite(led, LOW);
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(300);
  }
}
