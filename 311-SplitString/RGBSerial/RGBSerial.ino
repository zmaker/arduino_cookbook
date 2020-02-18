/*
 Il messaggio ricevuto deve sempre terminare con ;
 mi aspetto esattamente 4 valori: 3 rgb e una stringa
 * 
 */

int r, g, b;
String msg = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
      String line = Serial.readStringUntil('\n');
      
      if (line.length() > 0) {
        //Serial.println(line);  
        int m = 0;
        int n = line.indexOf(";");
        int indice = 0;
        while (n > 0) {
          String token = line.substring(n, m);
          //Serial.println(token);
          m = n+1;
          n = line.indexOf(";", n+1);

          //elaboro il token:
          processToken(indice, token);
          indice++;
        }
        //applico i risultati
        setRGB();
      }
  }
}

void processToken(int i, String str){
  switch(i){
    case 0:
      r = str.toInt();
      break;
    case 1:
      g = str.toInt();
      break;
    case 2:
      b = str.toInt();
      break;
    case 3:
      msg = str;
      break;
      
  }
}

void setRGB(){
  Serial.println(msg);
  analogWrite(3, r);
  analogWrite(5, g);
  analogWrite(6, b);
  }
