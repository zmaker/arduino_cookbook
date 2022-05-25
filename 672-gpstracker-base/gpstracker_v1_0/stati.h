#ifndef _STATI_H_
#define _STATI_H_

#define _SETUP_BEGIN_ if (FIRST) { 
#define _SETUP_END_ FIRST = false; }

//definizioni
void go(enum stati st);
void act_startup(Stream *out);
void act_work(Stream *out);
void act_getposition(Stream *out);
void act_callservice(Stream *out);

//implementazioni
void go(enum stati st){
  stato = st; 
  FIRST = true; 
}
void act_startup(Stream *out){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("startup");
  _SETUP_END_ 
  
  //codice da ripetere nello stato
  delay(2000);
  go(work);
}

void act_work(Stream *out){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("work");
    t1 = millis();
  _SETUP_END_ 
  
  //codice da ripetere nello stato
  if ((millis() - t1) > TIMEOUT_SENSORE) {
    //leggo i dati e procedo all'invio     
    go(getposition); 
  }
}

void act_getposition(Stream *out){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("getposition");
  _SETUP_END_ 
  
  //codice da ripetere nello stato

  position.lat = 45.5637;
  position.lon = 9.67453;
  position.alt = 100.1;
  delay(2000);
  go(callservice);
}

void act_callservice(Stream *out){
  _SETUP_BEGIN_
    //codice da eseguire all'ingresso dello stato
    out->println("call service");
  _SETUP_END_ 
  
  //codice da ripetere nello stato
  delay(2000);
  go(work);
}

#endif
