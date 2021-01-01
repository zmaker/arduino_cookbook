#include <TimerOne.h>
#include <MultiFuncShield.h>

int stato = 0;
int counter = 0;
int c = 0;

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  //pin
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(3, OUTPUT); 

  stato = 99;
}

void loop() {
  switch (stato) {
    case 0:
    //imposto la cifra
    setcounter();
  break;
    case 1:
    //conteggio
    count();
  break;  
    case 2:
    //stop
    endcount();
  break; 
      case 99:
    //reset
    resetcounter();
  break;  
  }
}

bool tasto;
bool prev_tasto;
long dt,t0; //memorizza il numero di millis a inizio conteggio

void setcounter(){
  if (!digitalRead(A3)) {
    counter++;
    delay(300);
  }
  if (!digitalRead(A2)) {
    counter += 10;
    delay(300);
  }  

  //LONG PRESS su A1 - BEGIN - Sketch 031
  tasto = !digitalRead(A1);
  //individuo il fronte di salita
  if (!prev_tasto && tasto) {
    Serial.println("inizio conteggio");
    t0 = millis();
  }

  //durante la pressione
  if (prev_tasto && tasto) {
    dt = millis() - t0;
    if (dt > 1000) { //azzero conteggio
        counter = 0;
    }
  }
  
  //rilascio
  if (prev_tasto && !tasto) {
    if (dt < 1000) { //avvio conteggio
        MFS.blinkDisplay(DIGIT_ALL, OFF);
        stato = 1;
        //uso c come contatore e non il valore impostato (per non perderlo)
        c = counter;
    }
  }
 
  //salvo il valore di stato in prev_stato
  prev_tasto = tasto;
  //LONG PRESS su A3 - END
  
  if (counter >= 9999) counter = 0;
  MFS.write((int)counter);
}

void count() {
  MFS.write((int)c);
  delay(1000);
  c--;  
  if (c <= 0) stato = 2; 
}

void endcount() {
  MFS.write("End");
  MFS.blinkDisplay(DIGIT_ALL, ON);
  delay(3000);
  stato = 0;
}

void resetcounter(){
  MFS.blinkDisplay(DIGIT_ALL, ON);
  stato = 0;
}
