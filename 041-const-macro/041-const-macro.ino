#define CFZ(R) 2*3.14*R
#define PRT(S) Serial.print(S); 
#define PRTN(S) Serial.println(S); 

void setup() {
  Serial.begin(9600);

  int c = CFZ(10);
  
  PRT("cfz=");
  PRTN(c);
}

void loop() {  }
