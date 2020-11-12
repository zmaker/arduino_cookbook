/**
 * Lettore SD
 */
#include <SPI.h>
#include <SD.h>
File file;
String messaggio;
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
byte mapping[13][2] = {
  {'a', 0},
  {'b', 1},
  {'c', 0},
  {'d', 0},
  {'e', 3},
  {'f', 0},
  {'g', 0},
  {'h', 2},
  {'i', 0},
  {'l', 4},
  {'m', 0},
  {'n', 0},
  {'o', 5}
  };
byte alpha[6][5] = {
  {
    B00011000,
    B00100100,
    B01000010,
    B01111110,
    B01000010
  },
  {
    B01111000,
    B01000100,
    B01111000,
    B01000100,
    B01111100
  },
  {
    B01000100,
    B01000100,
    B01111100,
    B01000100,
    B01000100
  },
  {
    B01111100,
    B01000000,
    B01111000,
    B01000000,
    B01111100
  },  
  {
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01111100
  }, 
  {
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B00111000
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

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }

  readfile("dati.txt");
}

int xs = 0;

void loop() {
  
  //estraggo i caratteri di messaggio e li stampo    
  for (int i = 0; i < messaggio.length(); i++) {
    char c = messaggio.charAt(i);
    //ricavo l'array da visualizzare
    //la sua posizione 
    int id = findInMap(c);
    //visualizzo lo sprite con la lettera
    int xlettera = xs + i*8;
    drawSprite(xlettera,1, alpha[id]);
  } 
  

  delay(100);
  
  //pixel(10,1, true); 
  //drawSprite(xs,1, sprite);
  //delay(100);
  xs++;
  if (xs >= MAXBARX) xs = 0; 
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

void readfile(String fname) {
  //apro il file in lettura
  File file = SD.open(fname); 
  if (file) {
    while (file.available()) {
      char c = file.read();
      if (c == '\n') {
        //Serial.println("N");
        //Serial.println(messaggio);
      } else if (c == '\r') {
        //Serial.println("R");
      } else {
        messaggio += c;
        //Serial.println(c);
      }  
    }
    file.close();
  } else {
    Serial.print("error opening ");
    Serial.println(fname);
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
