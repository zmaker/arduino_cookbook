int s1, prevs1, s2, prevs2;
int stato;

#define FDS2 1
#define FDD2 2
#define FDS3 3
#define FDD3 4
#define QUIET 0

unsigned long t1 = 0;

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

  switch(stato) {
    case 0:
      Serial.println("0");
      if (n == FDS2) {
        tim(); //avvio il timer
        stato = 1; 
      }
      if (n == FDS3) {
        tim();
        stato = 6;           
      }
      break;  
    case 1:
      Serial.println("1");
      if (n == FDD2) {
        tim();
        stato = 2;
      }
      if (timeout()) stato = 0;           
      break;
    case 2:
      Serial.println("2");
      if (n == FDS3) {
        tim();
        stato = 3;
      }
      if (timeout()) stato = 0;           
      break;
    case 3:
      Serial.println("3");
      if (n == FDD3) {
        tim();
        stato = 4;  
      }
      if (timeout()) stato = 0;                     
      break;
    case 4:
      Serial.println("2 -> 3");
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      stato = 0;
    break;
    
    case 6:
      Serial.println("6");
      if (n == FDD3) {
        stato = 7; 
        tim();
      }
      if (timeout()) stato = 0;                      
      break;  
    case 7:
      Serial.println("7");
      if (n == FDS2) {
        tim();
        stato = 8; 
      }
      if (timeout()) stato = 0;                      
      break;
    case 8:
      Serial.println("8");
      if (n == FDD2) {
        tim();
        stato = 9;
      }
      if (timeout()) stato = 0;           
      break;    
    case 9:
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

void tim() {
  t1 = millis();  
}

bool timeout() {
  if ((millis() - t1) >= 1000) {
    return true;
  } else {
    return false;
  }
  
}
