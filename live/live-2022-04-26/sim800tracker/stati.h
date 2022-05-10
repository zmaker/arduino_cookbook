#ifndef STATI_H
#define STATI_H

#define SETUP_BEGIN if (FIRST) {
#define SETUP_END FIRST = false; }

/* dichiarazione delle funzioni di stato */

/* funzioni di servizio */
void go(enum stati st);

void act_startup();
void act_work();
void act_getposition();
void act_callservice();

/**-----------------------------------------
   implementazione delle funzioni di stato */

void go(enum stati st){
  stato = st;
  FIRST = true;
}

void act_startup(){ 
  SETUP_BEGIN
  Serial.println("startup");
  //codice da eseguire una volta
  SETUP_END
}
void  act_work(){
  SETUP_BEGIN
  //codice da eseguire una volta
  SETUP_END
}
void act_getposition(){
  SETUP_BEGIN
  //codice da eseguire una volta
  SETUP_END
}
void act_callservice(){
  SETUP_BEGIN
  //codice da eseguire una volta
  SETUP_END
}

#endif
