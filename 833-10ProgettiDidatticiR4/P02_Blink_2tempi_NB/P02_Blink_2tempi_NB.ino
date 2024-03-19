/* #2 - Blink non bloccante a due tempi
 - LED su D5
*/

//pin del LED
int led = 5;

//tempo salvato del'utlimo blink
unsigned long t1;
//differenza tra ora e l'ultimo blink
unsigned long dt;
//tempo di attesa del timer
unsigned long t_fase;


//i tempi del blink
#define T_BLINK_1 800l
#define T_BLINK_2 200l

void setup() {
  //imposto il pin di uscita
  pinMode(led, OUTPUT);
  //salvo il tempo iniziale
  t1 = millis();
  //imposto il tempo della prima fase
  t_fase = T_BLINK_1;
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
      t_fase = T_BLINK_2;
    } else {
      t_fase = T_BLINK_1;
    }

    //salvo il tempo corrente
    t1 = millis();
  }

}
