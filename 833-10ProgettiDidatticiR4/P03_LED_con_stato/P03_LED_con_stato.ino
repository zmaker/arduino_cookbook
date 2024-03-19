/* #3 - LED con stato

Versione semplice senza debouncing o rilevazione 
dei fronti di salita o discesa. 
Utilizza una semplice delay

Lo stato del LED è mantenuto dal pin stesso

 - LED su D5
 - BUTTON su D2
*/

//pin del LED
int led = 5;

//pin del pulsante
int bt = 2;

void setup() {
  //imposto i pin
  pinMode(led, OUTPUT);
  pinMode(bt, INPUT);

  //imposto il pin inizialmente spento
  digitalWrite(led, LOW);
}

void loop() {
  //se il tasto viene premuto
  if (digitalRead(bt)) {
    //cambio lo stato del LED
    digitalWrite(led, !digitalRead(led));
    //attendo che i rimbalzi cessino (poor-man debouncing)
    delay(500);
  }  
}
