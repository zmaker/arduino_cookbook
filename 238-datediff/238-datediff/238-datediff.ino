void setup() {
  Serial.begin(9600);
  int d = ddcount(20, 6, 2019, 7, 3, 2017);
  Serial.println(d); 
}


void loop() {

}

int ddcount(int d1, int m1, int y1, int d0, int m0, int y0){
  //data1 è maggiore di data 0
  int n = 0;
  if (y1 < y0) return 0;  
  //calcolo i giorni a partuire dal 1 gennaio dell'anno della prima data (0)
  int gg0 = d0;
  for (int i = 1; i <= (m0-1); i++) {
    int m = getGiorniMese(i, y0); 
    gg0 += m; 
  }
  //calcolo i giorni della seconda data a partire dal 1 gennaio della data 1
  int gg1 = d1;
  for (int i = 1; i <= (m1-1); i++) {
    gg1 += getGiorniMese(i, y1);  
  }
  for (int i = y0; i <= (y1-1) ; i++) {
    gg1 += getGiorniAnno(i);  
  }
  n = gg1 - gg0;
  
  return n;
}

int gmese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int getGiorniMese(int mm, int yy){
  int m = mm - 1;
  if ((m == 1) && (yy%4 == 0)) {
    return 29;
  } else {
    m = gmese[m];
  }
  return m;
}

int getGiorniAnno(int yy){
  if (yy%4 == 0) {
    return 366;
  }
  return 365;
}
