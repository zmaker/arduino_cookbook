/* #8 - Blink non bloccante e regolabile
 - LED su D5
 - POT su A0
*/

//pin del LED
int led = 5;

//pin del pot
int pot = A0;

//tempo salvato del'utlimo blink
unsigned long t1;
//differenza tra ora e l'ultimo blink
unsigned long dt;
//tempo di attesa del timer
unsigned long t_fase;

//durata totale del blink
unsigned long tmax = 1000l;
//tempi "regolati"
unsigned long tblink1 = 500l;
unsigned long tblink2 = tmax - 500l;

void setup() {
  //imposto il pin di uscita
  pinMode(led, OUTPUT);
  //salvo il tempo iniziale
  t1 = millis();
  //imposto il tempo della prima fase
  t_fase = tblink1;
  //imposto lo stato iniziale del LED
  digitalWrite(led, LOW);
}

void loop() {
  //calcolo la differenza dall'ultimo blink
  dt = millis() - t1;
  //se dt maggiore del tempo di blink...
  if (dt > t_fase) {
    //è ora di cambiare
    //inverto lo stato dell'uscita
    digitalWrite(led, !digitalRead(led));
    //uso lo sttao del LED per impostare il tempo
    if (digitalRead(led)) {
      t_fase = tblink2;
    } else {
      t_fase = tblink1;
    }

    //salvo il tempo corrente
    t1 = millis();
  }

  //leggo il potenziometro e calcolo i tempi
  int val = analogRead(A0);
  tblink1 = map(val, 0, 1023, 0, 999);
  tblink2 = tmax - tblink1;
}
