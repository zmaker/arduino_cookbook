/* 
Controllo vasca con due galleggianti simulati con 2 tasti
(esempio di macchina a stati)

D2: galleggiante livello minimo della vasca
D3: galleggiante livello massimo della vasca

La pompa va collegata al pin 13, qui sintetizzata con un LED

min MAX | pompa | stato
-----------------------
 0   0  |   0   |   1
 1   0  |   0   |   2
 1   1  |   1   |   3
 1   0  |   1   |   4
 
 regole: 
 da s1: posso andare a s2
 da s2: posso andare a s1 o s3
 da s3: posso andare solo in s4
 da s4: in s1 o tornare in s3

La pompa è:
 spenta in s1
 spenta in s2
 accesa in s3
 accesa in s4
 
*/
int stato = 1;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {  
  //leggo i galleggianti
  int lmin = digitalRead(2);
  int lmax = digitalRead(3);
  
  String str = "s: " + String(stato) + 
    " min: " + String(lmin) + " max:" + String(lmax);
  Serial.println(str);
  
  switch (stato){
    case 1:
      digitalWrite(13, LOW);
      //cambio di stato se:
      if (lmin && !lmax) stato = 2;
    break;   
    case 2:
      digitalWrite(13, LOW);
      //cambio di stato se:
      if (lmin && lmax) stato = 3;
      if (!lmin && !lmax) stato = 1;
    break;
    case 3:
      digitalWrite(13, HIGH);
      //cabio di stato se:
      if (lmin && !lmax) stato = 4;
    break;
    case 4:
      digitalWrite(13, HIGH);
      //cabio di stato se:
      if (lmin && lmax) stato = 3;
      if (!lmin && !lmax) stato = 1;
    break;
  }  
  
  delay(200);
}
