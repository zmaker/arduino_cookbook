/*
Copia di array
*/

int seq[] = {1,2,3,4,5,6,8,5,67,100};

void setup() {
  Serial.begin(9600);
  
  //copia con ciclo for
  int copia[sizeof(seq)/sizeof(int)];
  
  for (int i = 0; i < (sizeof(seq)/sizeof(int)); i++){
    copia[i] = seq[i];
    Serial.println(copia[i]);
  }

  //copia memcpy
  int dest[sizeof(seq)/sizeof(int)];
  memcpy(dest, seq, sizeof(dest));

  Serial.println("leggo l'array dest");
  for (int i = 0; i < (sizeof(dest)/sizeof(int)); i++){
    Serial.println(dest[i]);
  }

}

void loop(){}
