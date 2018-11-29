#define DT 10
#define SETPOINT 20

float kp = 3;  //3
float ki = 10; //10;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  //lettura
  int v = analogRead(A0);  
  //calcolo errore
  float e = v - SETPOINT;  

  //calcolo output da applicare
  int out = (int)(prop(e) + intgr(e));
  out = map(out, 0, 510, 0, 255);
  out = constrain(out, 0, 255);
  analogWrite(11, out);

  //Serial.print("v:");
  //Serial.print(v);
  //Serial.print("\te:");
  //Serial.print(e);
  //Serial.print("\to:");
  //Serial.println(out);
  Serial.println(e);
  
  delay(DT);
}

float prop(float e) {
  float p = e*kp;
  return p;  
}

#define blen 100
float buf[blen];

float intgr(float e) {
  buf[0] = e;
  for (int j = blen-1; j > 0; j--) {
    buf[j] = buf[j-1];
  }
  
  float m = 0;
  for (int j = 0; j < blen; j++){    
    m += buf[j];
  }
  m = m / (float)blen;  
  float i = m*ki;
  return i;  
}
