#include "morse.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 


#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  
}

const int THR_LOW = 600;
const int THR_HI = 700;

unsigned long tref = 100;
unsigned long t1, dt;
String morse = "";
int stato = 0;

void loop() {
  switch(stato) {
    case 0:
      waitTx();
      break;
    case 10:
      measureSgn();
      break;
    case 20:
      decodeSign();
      break; 
    case 30:
      measurePause();
      break;
    case 40:
      decodeMorse();
      break;
    case 50:
      resetTx();
      break;
  }

}

bool FIRST = true;

void waitTx(){
  if (FIRST) {
    //Serial.println("listen...");
    FIRST = false;      
  }
  if (analogRead(A0) > THR_HI) {
    go(10);
    t1 = millis();
  }   
}
void measureSgn(){
  if (FIRST) {
    //Serial.println("measure...");
    FIRST = false;  
  }
  if (analogRead(A0) < THR_LOW) {
    go(20);
    dt = millis() - t1;
  }   
}
void decodeSign(){
  if (FIRST) {
    //Serial.print("dt=");
    //Serial.println(dt);
    FIRST = false;  
  }
  if (dt < tref) {
    //punto
    morse += ".";  
    //Serial.println(".");
  } else if ((dt > 2*tref) && (dt < 7*tref)) {
    //linea  
    morse += "-";
    //Serial.println("-");
  }
  t1 = millis();
  go(30);
}
void measurePause(){
  if (FIRST) {
    //Serial.println("silence...");
    FIRST = false;  
  }
  dt = millis() - t1;
  if (dt > 2*tref) {
      //decodifico il morse
      go(40);
  }
  if (analogRead(A0) > THR_HI) {
    //proseguo a raccogliere segni
    go(0);
  }
}

String letter;

void decodeMorse(){
  if (FIRST) {
    //Serial.println(morse);
    FIRST = false;  
  }
  for (int i = 0; i < NUMITEMS(letters)/2; i++){
    String code = letters[i*2 + 1];
    if (code == morse) {
      String letter = letters[i*2];
      Serial.println(letter);  
      toDisplay(letter);
      
      break;
    }  
  }  
  go(50);
}

void resetTx(){
  if (FIRST) {
    //Serial.println("reset");
    FIRST = false;  
  }
  morse = "";
  go(0);
}

void go(int s) {
  stato = s; 
  FIRST = true; 
}

char buff[12];
int p = 0;

void toDisplay(String l) {
  buff[p] = l.charAt(0);
  p++;
  if (p == 12) {
    p = 0;
  }
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_unifont);
  
    u8g.drawStr( 0, 22, buff);   
  } while( u8g.nextPage() );  
}
