/* centro di massa di un array per trovare la posizione */
int set1[10] = {0,0,0,0,100,0,0,0,0,0};
int set2[10] = {0,0,0,50,50,0,0,0,0,0};
int set3[10] = {0,0,0,30,80,70,0,0,0,0};

void setup() {
  Serial.begin(9600);

  float p = getIndice(set1);
  Serial.print("p: ");Serial.println(p);
  p = getIndice(set2);
  Serial.print("p: ");Serial.println(p);
  p = getIndice(set3);
  Serial.print("p: ");Serial.println(p);

}

void loop() {
  // put your main code here, to run repeatedly:
}

float getIndice(int valori[]){
  float sommaMomenti = 0;
  float sommaValori = 0;

  for (int i = 0; i < 10; i++) {
    sommaMomenti += valori[i] * i;
    sommaValori += valori[i];
  }

  float pos = 0;
  if (sommaValori > 0) {
    pos = sommaMomenti / sommaValori;
  }
  
  return pos;
}







