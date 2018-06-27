int matrice[4][4] = {  //[righe][colonne]
  {1 ,2 ,3 , 4},
  {11,12,13,14}, 
  {21,22,23,24},
  {31,32,33,34}
};
 
int cubo[3][3][3];

void setup(){
  Serial.begin(9600);
  
  for(int r = 0; r < 4; r++){ //riga 
    for(int c = 0; c < 4; c++){ //colonna
      int cella = matrice[r][c]; 
      String str = String(cella) + " ";
      Serial.print(str);
    }//close for j 
    Serial.println("\n");
  }//close for i
 }

void loop(){
}
