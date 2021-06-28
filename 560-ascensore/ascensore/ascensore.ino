int b2, prevb2;
bool UP, DN;
int level = 0;
int stato = 0;

void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  b2 = digitalRead(2);
  DN = digitalRead(3);
  UP = digitalRead(4);
  
  switch (stato) {
    case 0:
        digitalWrite(10+level, HIGH);
      if ((UP) && (prevb2 && !b2)) { //UP + FDD lamella
          stato = 1;
      }
        if ((DN) && (prevb2 && !b2)) { //DN + FDD lamella
          stato = 2;
      }
      break;
    case 1:
        digitalWrite(10+level, LOW);
        if (!prevb2 && b2) { //FDS lamella
          level++;
          if (level > 2) level = 2;
          stato = 0;    
      }
      break;
    case 2:
        digitalWrite(10+level, LOW);
        if (!prevb2 && b2) { //FDS lamella
          level--;
          if (level < 0) level = 0;
          stato = 0;    
      }
      break;
  }

  
  prevb2 = b2;
}
