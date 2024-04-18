// shuffle array

//dimensione array
#define ELEMENTI 10

//array iniziale
int numeri[ELEMENTI];

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(1);
  //popola array
  popolaArray(numeri, ELEMENTI);
  printa(numeri, ELEMENTI);

  //mescola array
  shuffle(numeri, ELEMENTI);
  printa(numeri, ELEMENTI);
}

void loop() {}

void printa(int *n, const int len){
  for (int i = 0; i < len; i++) {
    Serial.print(n[i]);
    Serial.print("\t");
  }
  Serial.println(""); 
}

void popolaArray(int *n, const int len){
  for (int i = 0; i < len; i++) {
    n[i] = i+1;
  }
}

void shuffle(int *n, const int len){
  randomSeed(analogRead(A0));
  for (int i = 0; i < len*2; i++){
    //indice a caso tra 0 e len-2
    int j = random(len-1);
    //Serial.println(j);
    //scambio gli elementi
    int t = n[j];
    n[j] = n[j+1];
    n[j+1] = t;
  }
}
