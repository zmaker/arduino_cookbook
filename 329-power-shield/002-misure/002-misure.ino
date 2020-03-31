void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  
  //SW1 OFF per abilitare il pin 13
  //SW2 se è su ON ho le letture sugli A0-A5
  //Con sw1 in OFF le letture sono su 
  /* 
  A0 - protection signal
  A1 - warning
  A2 - misura della corrente
  */ 
  pinMode(A0, INPUT);   
  pinMode(A1, INPUT); 

  delay(4000);
  digitalWrite(13, HIGH);
  
}


void loop() {
  int v = analogRead(A2);
  float i = ((float)v)* (50.0/1024.0);
  Serial.println(i);
  delay(10);
}
