/* #1 - Blink non bloccante
 - LED su D5
*/

//pin del LED
int led = 5;

//tempo salvato del'utlimo blink
unsigned long t1;
//differenza tra ora e l'ultimo blink
unsigned long dt;

//il tempo del blink
#define T_BLINK 750l

void setup() {
  //imposto il pin di uscita
  pinMode(led, OUTPUT);
  //salvo il tempo iniziale
  t1 = millis();
}

void loop() {
  //calcolo la differenza dall'ultimo blink
  dt = millis() - t1;
  //se dt maggiore del tempo di blink...
  if (dt > T_BLINK) {
    //inverto lo sttao dell'uscita
    digitalWrite(led, !digitalRead(led));
    //salvo il tempo corrente
    t1 = millis();
  }

}
