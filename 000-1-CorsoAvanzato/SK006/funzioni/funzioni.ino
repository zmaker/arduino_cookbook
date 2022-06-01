void ledBlink();
void ledBlinkConParametri(int n, int tm);
int somma(int a, int b);
String esclama(String msg);

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);

  //ledBlink();
  int tempo = 200;
  //ledBlinkConParametri(7, tempo);

  int res = somma(10, 25);
  Serial.println(res);

  String ans = esclama("ciao");
  Serial.println(ans);
}

void loop() {

}

void ledBlink(){
  int stato = LOW;
  for (int i = 0; i < 6; i++) {
    digitalWrite(3, stato);
    stato = !stato;
    delay(500);
  }
}

void ledBlinkConParametri(int n, int tm){
  int stato = LOW;
  for (int i = 0; i < n; i++) {
    digitalWrite(3, stato);
    stato = !stato;
    delay(tm);
  }
}

int somma(int a, int b) {
  int s = a + b;
  return s;
}

String esclama(String msg){
  return msg + "!";
}
