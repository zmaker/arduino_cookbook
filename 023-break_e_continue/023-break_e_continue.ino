/*
Arduino Cookbook - di Paolo Aliverti
www.zeppelinmaker.it

Effetto di break e continue
*/

void setup() {
  Serial.begin(9600);
  
  Serial.println("FOR - uso di break ");
  for (int j = 0; j < 10; j++){
    if (j == 5) break;
    Serial.print("j: ");
    Serial.println(j);   
  }
  Serial.println("FOR - uso di continue ");
  for (int j = 0; j < 10; j++){
    if (j == 5) continue;
    Serial.print("j: ");
    Serial.println(j);   
  }

  Serial.println("WHILE - uso di break ");  
  int i = 0;   
  while (i < 10) {
    Serial.print("i: ");
    Serial.println(i);
    if (i == 5) break;
    i++;
  }
  Serial.print("uscito con i: ");
  Serial.println(i);
  
  i = 0;  //riazzero i
  Serial.println("WHILE - uso di continue ");
  while (i < 10) {
    if (i == 5) {
      i++;
      continue;
    }
    Serial.print("i: ");
    Serial.println(i);    
    i++;
  }

}

void loop(){}
