void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
}

unsigned int Htime, Ltime;
float Ttime, freq;

void loop() {  
  Htime=pulseIn(8,HIGH);      //read high time
  Ltime=pulseIn(8,LOW);        //read low time

  Ttime = Htime+Ltime;
  freq=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds

  Serial.println(freq);
  
  delay(500);
}
