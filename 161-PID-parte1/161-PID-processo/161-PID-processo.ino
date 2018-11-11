#define DATALEN 100
#define TEMPODISTURBO 1000
#define DISTURBO 50

byte buf[DATALEN];

void setup() {
  Serial.begin(9600);  
}

unsigned long t = TEMPODISTURBO;
int stato_disturbato = 1;

void loop() {
  int v = analogRead(A0);

  if (t == 0) { 
    t = TEMPODISTURBO;
    stato_disturbato = -stato_disturbato;   
    //Serial.println("DIST"); 
  }
  t--;

  v += DISTURBO * stato_disturbato;
  
  int n = map(v, 0, 300, 255, 0);
  n = constrain(n, 0, 255);

  buf[0] = n;
  for (int i = DATALEN-1; i > 0; i--){
    buf[i] = buf[i-1];     
    /*     
    Serial.print("i=");
    Serial.print(i-1);
    Serial.print("\tbuf=");
    Serial.println(buf[i-1]);
    */    
  }  
  
  analogWrite(11, buf[DATALEN-1]);    
  //Serial.print("\tbuf=");
  //Serial.println(buf[DATALEN-1]);
  delay(10);
}
