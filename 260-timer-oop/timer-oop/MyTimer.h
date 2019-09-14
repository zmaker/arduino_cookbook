#ifndef mytimer_h
#define mytimer_h

class MyTimer {
  private:
  int tempo;
  unsigned long t1, dt;
  int attivo = 0;
  
  public:
  MyTimer();

  void set(int);
  int check();
};

MyTimer::MyTimer() {
  attivo = 0;  
}

void MyTimer::set(int n){
  tempo = n;
  t1 = millis();
  attivo = 1;
}

int MyTimer::check(){
  int ret = 0;
  if (attivo == 1) {
    dt = millis() - t1;
    if (dt >= tempo) {
      ret = 1;
      attivo = 0;
    }
  } else {
    ret = 0;
  }
  return ret;
}

#endif
