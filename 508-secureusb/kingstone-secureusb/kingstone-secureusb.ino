/**
 * https://playground.arduino.cc/Code/Keypad/
 */
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[ROWS] = {4,3,2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//display
#include <Adafruit_SSD1306.h>
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    abort();
  }
  display.display();
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.clearDisplay();
  display.print("OK");
  display.display();
}

char combinazione[20];
char password[20] = "1234";
int pos = 0;
unsigned long t1, dt;
bool ATTIVO;

void loop() {
  char key = keypad.getKey();
  if (key) {
    //Serial.println(key);
    if (key == '*') {
      //azzera
      pos = 0;
      combinazione[pos] = 0;
    } else if (key == '#') {
      if (ATTIVO) {
        disattiva();  
      } else {
        verifica(combinazione);
      }
    } else {
      combinazione[pos] = key;
      pos++;
      combinazione[pos] = 0;
      Serial.println(combinazione);
    }
  }

  dt = millis() - t1;
  if (dt > 100) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(combinazione);
    if (ATTIVO) {
      display.setCursor(0,16);
      display.print("CONNESSO");
    } else {
      display.setCursor(0,16);
      display.print("OFF");
    }
    display.display();
    t1 = millis();    
  }
}

void verifica(char *str){
  Serial.print("str: ");
  Serial.println(str);
  Serial.print("pwd: ");
  Serial.println(password);
  if (strcmp(str, password) == 0) {
    attiva();      
  } else {
    disattiva();  
  }
}

void attiva() {
  ATTIVO = true;
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void disattiva() {
  ATTIVO = false;
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  display.clearDisplay();
  combinazione[0] = 0;
  pos = 0;
  display.display();
}
