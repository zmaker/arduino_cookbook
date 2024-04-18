// CRC 
//

//dati
uint8_t dati[12] = {1,0,1,0,1,0,1,0,1,1,0,1};

//polinomio
uint8_t poli[4] = {1,0,1,1};

//dati estesi
uint8_t dati_estesi[12+4-1];

//resto
uint8_t resto[4-1];

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Serial.println("CRC");

  prtb(dati, 12);

  //creo i dati estesi copiando i dati e aggiungendo 4-1 posizioni a destra
  estendi_dati(dati, 12, 4, dati_estesi);
  prtb(dati_estesi, 15);

  int step = 1;
  int shifts = 1;
  while (shifts <= 12) {
  //prima divisione con XOR
  Serial.print("STEP ");Serial.println(step);
  for (int i = 0; i < 4; i++) {
    uint8_t a = dati_estesi[i];
    uint8_t b = poli[i];
    uint8_t r = a ^ b;
    dati_estesi[i] = r;
  }
  prtb(dati_estesi, 15);

  //verifico se il primo bit è zero
  while (dati_estesi[0] == 0) {
    //scorro a sinistra
    Serial.print("SHIFT "); Serial.println(shifts);
    shiftBitsLeft(dati_estesi, 15);
    prtb(dati_estesi, 15);
    shifts++;
  }
  step++;
  }
  //estraggo il resto
  for (int i = 0; i < (4-1); i++) {
    resto[i] = dati_estesi[i];
  }
  Serial.println("RESTO"); 
  prtb(resto, 3);
}

void loop(){

}

void prtb(uint8_t *dt, uint8_t len){
  for (int i = 0; i < len; i++) {
    Serial.print(i);
    Serial.print("\t");
  }
  Serial.print("\n");
  for (int i = 0; i < len; i++) {
    uint8_t ch = dt[i];
  	Serial.print(ch);
    Serial.print("\t");
  }
  Serial.println("");
}

void estendi_dati(uint8_t *dt, uint8_t len, uint8_t polilen, uint8_t *de){
  //copio i dati nel array esteso
  for (int i = 0; i < len; i++) {
    de[i] = dt[i];
  }
  //aggiungo polilen-1 zeri a destra
  for (int i = len; i < len-1+polilen-1; i++) {
    de[i] = 0;
  }
}

void shiftBitsLeft(uint8_t *dt, uint8_t len){
  for (int i = 0; i < len-1; i++) {
    dt[i] = dt[i+1];
  }
  dt[len-1] = 0;
}