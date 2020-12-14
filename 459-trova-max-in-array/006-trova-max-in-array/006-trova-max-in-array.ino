int num[] = {12,32,3,45,56,34,36,98,67,43,67,87,67,2};

void setup() {
  Serial.begin(9600);

  int maxn = 0;
 
  for (int i = 0; i < sizeof(num)/sizeof(int); i++) {
    //Serial.println(i);  //stampa l'indice
    int n = num[i]; //estrae l'elemento
    if (n > maxn) {
      maxn = n;
    }
  }
  Serial.print("max = ");
  Serial.println(maxn);
}

void loop() {
}
