#ifndef _STATI_H_
#define _STATI_H_

#define _SETUP_BEGIN_ if (FIRST) {
#define _SETUP_END_ FIRST = false;}

enum stati {inizia, running, fase1, fase2};
enum stati stato = inizia;
bool FIRST = true;

//dichiarazione delle funzioni
void go(enum stati st);
void act_inizia(Stream *out);
void act_running(Stream *out);
void act_fase1(Stream *out);
void act_fase2(Stream *out);

//implementazione
void go(enum stati st){
  stato = st;
  FIRST = true;
}

void act_inizia(Stream *out){
  _SETUP_BEGIN_
  out->println("inizia");
  _SETUP_END_
  
  delay(1000);
  go(running);
}

void act_running(Stream *out){
  _SETUP_BEGIN_
  out->println("running");
  _SETUP_END_

  delay(1000);
  go(fase1);
}

void act_fase1(Stream *out){
  _SETUP_BEGIN_
  out->println("fase1");
  _SETUP_END_  

  delay(1000);
  go(fase2);
}

void act_fase2(Stream *out){
  _SETUP_BEGIN_
  out->println("fase2");
  _SETUP_END_

  delay(1000);
  go(inizia);
}

#endif
