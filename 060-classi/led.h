#ifndef led_h
#define led_h

class Led {
  private:
  int stato;
  int led;
  
  public:
  Led();
  Led(int);

  void turnOn();
  void turnOff();
  String toString();
};

Led::Led(){
  stato = LOW;
  led = 13;
}
Led::Led(int n){
  stato = LOW;
  led = n;
}

void Led::turnOn(){
  stato = HIGH;
}
void Led::turnOff(){
  stato = LOW;
}
String Led::toString(){
  String str = "Led " + String(led) + " st:";
  if (stato == HIGH) {
    str += "Acceso";
  } else {
    str += "Spento";
  }
  return str;
}

#endif
