struct sensore {
  char nome[20];
  int led;
  int temperatura;
};

struct sensore s1;
struct sensore s2 = {"t.ext", LOW, 0};

void setup() {
 Serial.begin(9600);
 s1.temperatura = analogRead(A0);
 
 Serial.println(s1.temperatura);

  Serial.println(s2.nome);
  Serial.println(s2.led);
  Serial.println(s2.temperatura);
 
}

void loop() {

}
