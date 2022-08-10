#include "JoyShield.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long t1;
int sz = 3;

enum directions {none, up, down, left, right} dir;

//1 aggiungo due array lunghi con coordinate e direzione.
//posso usare byte perché al max ho 128 char
#define MAX_SNAKE 20
byte x[MAX_SNAKE];
byte y[MAX_SNAKE];
enum directions dirl[MAX_SNAKE];
byte snake_len = 3;
int fx, fy;

void setup() {
  Serial.begin(9600);
  
  if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  oled.setTextSize(1);      // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE); // Draw white text
  oled.cp437(true);         // Use full 256 char 'Code Page 437' font

  //2 inizializzo gli array
  for (byte i = 0; i < MAX_SNAKE; i++) {
    x[i] = 0;
    y[i] = 0;
    dirl[i] = none;
  }
  x[0] = SCREEN_WIDTH / 2;
  y[0] = SCREEN_HEIGHT / 2;
  dirl[0] = up;
  x[1] = SCREEN_WIDTH / 2;
  y[1] = SCREEN_HEIGHT / 2+sz;
  dirl[1] = up;
  x[2] = SCREEN_WIDTH / 2;
  y[2] = SCREEN_HEIGHT / 2 + 2 * sz;
  dirl[2] = up;

  dir = up;

  randomSeed(analogRead(A2));  
  food();
}

void loop() { 
  int a = analogRead(AXIS_X);
  int b = analogRead(AXIS_Y);
  if (a > 768) dir = right;
  if (a < 256) dir = left;
  if (b > 768) dir = up;
  if (b < 256) dir = down;
  
  if ((millis() - t1) > 100) {
    oled.clearDisplay();

    //food    
    oled.fillRect(fx, fy, sz, sz, SSD1306_WHITE);    

    if (
      (x[0] >= fx) && (x[0] < fx+sz) &&
      (y[0] >= fy) && (y[0] < fy+sz)) {
      grow();    
    }

    drawSnake(dir);
         
    oled.display();  
    t1 = millis();    
  }
}

void drawSnake(enum directions dir){

  //draw
  for (int i = 0; i < snake_len; i++) {     
    oled.drawRect(x[i], y[i], sz, sz, SSD1306_WHITE);      
  }

  //move
  //qui assegno ad ogni blocco la direzione 
  enum directions dir_blocco_che_precede = 0;
  enum directions d = 0;
  Serial.println(x[0]);
  for (int i = 0; i < snake_len; i++) {    
    if (i == 0) {      
      //per il primo blocco
      //salvo la sua dir nella variabile dirprec
      dir_blocco_che_precede = dirl[0];
      //a lui assegno la direzione corrente
      dirl[0] = dir;
    } else {  
      //per i blocchi a seguire
      //salvo la direzione del blocco nella variabule d
      d = dirl[i];
      //nella dir del blocco metto dirprec
      dirl[i] = dir_blocco_che_precede;
      //salvo la sua dir nella variabile dirprec per assegnarla al prox blocco
      dir_blocco_che_precede = d;
    }
    //qui elaboro le direzioni dei blocchi
    switch(dirl[i]) {
      case up: //up
        y[i] -= sz;
        break;
      case down:  //dw
        y[i] += sz;
        break;
      case right: //lx
        x[i] += sz;
        break;
      case left:  //rx
        x[i] -= sz;
        break;
    }
    if (x[i] >= SCREEN_WIDTH) x[i] -= SCREEN_WIDTH;
    if (x[i] <= 0) x[i] += SCREEN_WIDTH;   
    if (y[i] >= SCREEN_HEIGHT) y[i] -= SCREEN_HEIGHT;
    if (y[i] <= 0) y[i] += SCREEN_HEIGHT;   
  }
  
}

void food() {
  fx = random(sz, SCREEN_WIDTH-sz);
  fy = random(sz, SCREEN_HEIGHT-sz);  
}

void grow() {
  if (snake_len == MAX_SNAKE - 1) return;
  
  int lastx = x[snake_len-1];
  int lasty = y[snake_len-1];
  enum directions lastdir = dirl[snake_len-1];

  switch(lastdir) {
    case up: //up
      lasty += sz;
      break;
    case down:  //dw
      lasty -= sz;
      break;
    case right: //lx
      lastx -= sz;
      break;
    case left:  //rx
      lastx += sz;
      break;
  }
  snake_len++;
  x[snake_len-1] = lastx;
  y[snake_len-1] = lasty;
  dirl[snake_len-1] = lastdir;
  
  //nuovo cibo
  food();
}
