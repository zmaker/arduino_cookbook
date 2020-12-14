#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 8
LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

#define MAXBARX (ELEMENTS*8)
byte mapping[12][2] = {
  {'0', 0},
  {'1', 1},
  {'2', 2},
  {'3', 3},
  {'4', 4},
  {'5', 5},
  {'6', 6},
  {'7', 7},
  {'8', 8},
  {'9', 9},
  {':', 10},
  {' ', 11}
  };
byte alpha[12][5] = {
  {
    B00011100,
    B00100010,
    B00100010,
    B00100010,
    B00011100
  },
  {
    B00001100,
    B00000100,
    B00000100,
    B00000100,
    B00000100
  },{
    B00011100,
    B00000010,
    B00011100,
    B00100000,
    B00111110
  },{
    B00011100,
    B00000010,
    B00001100,
    B00000010,
    B00011100
  },{
    B00010000,
    B00010000,
    B00010100,
    B00011110,
    B00000100
  },{
    B00111110,
    B00100000,
    B00011100,
    B00000010,
    B00111100
  },{
    B00011100,
    B00100000,
    B00111100,
    B00100010,
    B00011100
  },{
    B00111110,
    B00000010,
    B00000100,
    B00000100,
    B00001000
  },{
    B00011100,
    B00100010,
    B00011100,
    B00100010,
    B00011100
  },{
    B00011100,
    B00100010,
    B00011110,
    B00000010,
    B00011100
  },{
    B00000000,
    B00011000,
    B00000000,
    B00011000,
    B00000000
  },{
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS ; i++) {
    lc.shutdown(i,false);  // Wake up displays  
    lc.setIntensity(i,1);  // 0-15
    lc.clearDisplay(i);  // Clear Displays
  }
  Serial.println("ok");

  if (!rtc.begin()) {
    Serial.println("Controlla le connessioni");
    while(true);
  }

  if (rtc.lostPower()) {
    Serial.println("Imposto data/ora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

int i = 0;
char orario[] = "00:00:00";

void loop() {
  
  DateTime now = rtc.now();
  sprintf(orario, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  if (i%2 == 1) {
    orario[2] = ' ';
    orario[5] = ' ';  
  }
  i++;

  Serial.println(orario);
  
/*  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(pad(now.month()));
  Serial.print('/');
  Serial.print(pad(now.day()));
  Serial.print(" - ");
  Serial.print(pad(now.hour()));
  Serial.print(':');
  Serial.print(pad(now.minute()));
  Serial.print(':');
  Serial.print(pad(now.second()));
  Serial.println();
  */
 
  //estraggo i caratteri di messaggio e li stampo    
  for (int i = 0; i < sizeof(orario); i++) {
    char c = orario[i];
    //ricavo l'array da visualizzare
    //la sua posizione 
    int id = findInMap(c);
    //visualizzo lo sprite con la lettera
    int xlettera = i*8;
    drawSprite(xlettera,1, alpha[id]);
  } 

  delay(500);
}

void pixel(int x, int y, bool stato){  
  int el = (int)(x / 8);
  int xloc = 7-(x - (8*el));
  y = 7 - y;
  lc.setLed(el,y,xloc, stato);
}

void drawSprite(int xs, int ys, byte data[]){  
  for (int r = 0; r < 5; r++) {
    for (int i = 0; i < 8; i++) {
      bool pix = data[r] & (B10000000 >> i);
      if ((xs+i) <= MAXBARX) { 
        pixel(xs+i, ys+r, pix);
      }
    }
  }
}

int findInMap(char c){
  int ret = -1;
  for (int i = 0; i < 13; i++) {
    if (mapping[i][0] == c) {
        ret = mapping[i][1];
        break;
    }    
  }  
  return ret;
}
