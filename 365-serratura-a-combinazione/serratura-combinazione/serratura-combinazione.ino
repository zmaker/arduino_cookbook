#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void stato0();
void stato1();
void stato2();
void stato3();
void stato4();

typedef void (*fDiStato) ();

fDiStato stati[] = {stato0, stato1, stato2, stato3, stato4};

int stato = 0;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  stati[stato]();
}

String codice = "";
String password = "1234";
unsigned long t1;

void stato0() {
  char key = keypad.getKey();
  if (key) {
    t1 = millis();
    if (key == '#') {
      stato = 1;
    } else if (key == '*') {
      codice = "";
      Serial.println("azzero");
    } else {
      codice += key;
      Serial.println(codice);
    }
  }  

  if ((millis() - t1) > 5000) {
    stato = 4;  
  }
}
void stato1() {
  if (codice == password) {
    stato = 2;  
    Serial.println("ok");
  } else {
    stato = 3;  
    Serial.println("ko");
  }
}

void stato2() {
  Serial.println("s2");
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  stato = 4;
}
void stato3() {
  Serial.println("s3");
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
  stato = 4;  
}
void stato4() {
  Serial.println("reset");
  codice = "";
  stato = 0;
  t1 = millis();  
}
