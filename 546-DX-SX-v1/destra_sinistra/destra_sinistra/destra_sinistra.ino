int s1, prevs1, s2, prevs2;
int stato = 0;

#define FDS2 1
#define FDD2 2
#define FDS3 3
#define FDD3 4
#define QUIET 0

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  s1 = digitalRead(2);
  s2 = digitalRead(3);
  int n = fdds();
  prevs1 = s1;
  prevs2 = s2;

  switch(stato){
    case 0:
      if (n == FDS2) stato = 1;
      if (n == FDS3) stato = 4;
      break;  
    case 1:
      if (n == FDS3) stato = 2;  
      if (n == FDD2) stato = 0;  
      break;  
    case 2:
      if (n == FDD3) stato = 3;      
      break;  
    case 3:
      Serial.println("2 -> 3");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      stato = 0;
      break;
    case 4:
      if (n == FDS2) stato = 5;   
      if (n == FDD3) stato = 0;   
      break;  
    case 5:
      if (n == FDD2) stato = 6;      
      break;  
    case 6:
      Serial.println("3 -> 2");
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(12, LOW);
      stato = 0;
      break;
  }
}

int fdds() {
  int n = QUIET;
  if (s1 && !prevs1) {
     return FDS2;
  }
  if (!s1 && prevs1) {
     return FDD2;
  }
  if (s2 && !prevs2) {
     return FDS3;
  }
  if (!s2 && prevs2) {
     return FDD3;
  }
  return n;  
}
