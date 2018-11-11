#define SL_PE 3  //shiftload 
#define CP_CK 2  //CLK
#define Q7 7  //Q7
 
void setup() {
  pinMode(SL_PE ,OUTPUT);
  pinMode(CP_CK, OUTPUT);
  pinMode(Q7  ,INPUT);
  Serial.begin(9600);
}
 
void loop() {
  delay(1000);
  //load dei dati
  digitalWrite(SL_PE, LOW);  
  digitalWrite(CP_CK, LOW);  
  delay(10);    
  digitalWrite(CP_CK, HIGH);  
  digitalWrite(SL_PE, HIGH);
  delay(10);
  byte dati = shiftIn(Q7, CP_CK, MSBFIRST);
  Serial.print(dati, BIN);  
  Serial.println(" ");  
}
