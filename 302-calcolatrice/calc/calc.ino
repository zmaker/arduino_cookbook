#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;

const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
const int TS_LEFT=121,TS_RT=925,TS_TOP=85,TS_BOT=930;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button btn[12];

int stato = 0;
int key = -1;
int ans = 0;
int addendo = 0;

void setup() {
  Serial.begin(9600);
  int id = tft.readID();
  tft.begin(id);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);

  btn[1].initButton(&tft,  40,100, 60,40, WHITE, CYAN, BLACK, "1", 2);
  btn[2].initButton(&tft, 120,100, 60,40, WHITE, CYAN, BLACK, "2", 2);
  btn[3].initButton(&tft, 200,100, 60,40, WHITE, CYAN, BLACK, "3", 2);
  
  btn[4].initButton(&tft,  40,160, 60,40, WHITE, CYAN, BLACK, "4", 2);
  btn[5].initButton(&tft, 120,160, 60,40, WHITE, CYAN, BLACK, "5", 2);
  btn[6].initButton(&tft, 200,160, 60,40, WHITE, CYAN, BLACK, "6", 2);

  btn[7].initButton(&tft,  40,220, 60,40, WHITE, CYAN, BLACK, "7", 2);
  btn[8].initButton(&tft, 120,220, 60,40, WHITE, CYAN, BLACK, "8", 2);
  btn[9].initButton(&tft, 200,220, 60,40, WHITE, CYAN, BLACK, "9", 2);

  btn[10].initButton(&tft,  40,280, 60,40, WHITE, CYAN, BLACK, "+", 2);
  btn[0].initButton(&tft,  120,280, 60,40, WHITE, CYAN, BLACK, "0", 2);
  btn[11].initButton(&tft, 200,280, 60,40, WHITE, CYAN, BLACK, "=", 2);

  for (int i = 0; i < 12; i++) {
    btn[i].drawButton(false);
  }

  tft.fillRect(10, 10, 200, 40, WHITE);
}

int pixel_x, pixel_y;

void loop() {
  switch (stato) {
    case 0:
      readKeys();
      break;
    case 10:
      compose();
      break;
    case 20:
      add();
      break;
    case 30:
      answer();
      break;
  }
}

void compose(){
  addendo = addendo * 10 + key;
  prt(addendo);
  stato = 0;
}

void add(){
  ans += addendo;
  Serial.print("ans=");
  Serial.println(ans);
  addendo = 0;
  //prt(addendo);
  stato = 0;
}

void answer(){
  ans += addendo;
  Serial.print("ans=");
  Serial.println(ans);
  prt(ans);
  addendo = 0;
  ans = 0;
  stato = 0;  
}

void readKeys(){
  bool down = getPoint();
  for (int i = 0; i < 12; i++) {
    btn[i].press(down && btn[i].contains(pixel_x, pixel_y));
    
    if (btn[i].justPressed()) {
      btn[i].drawButton(true);      
    }
  
    if (btn[i].justReleased()) {
      btn[i].drawButton(false);
      pressKey(i);
      delay(100);
    }
  }
  
}

void prt(int n) {
  tft.fillRect(10, 10, 200, 40, WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 30);
  tft.setTextColor(BLACK);
  tft.print(n);
}

void pressKey(int n){
  Serial.println(n);
  if (n == 11) { //uguale
    stato = 30;
  } else if (n == 10) { //add
    stato = 20;
  } else { //compose
    stato = 10;
    key = n;
  }
}

bool getPoint(){
  bool pressed = false;
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  if ((p.z > MINPRESSURE) && (p.z < MAXPRESSURE)) {
    pressed = true;
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
    pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    /*Serial.print(p.x);
    Serial.print(" ");
    Serial.print(p.y);
    Serial.print("\t");
    Serial.print(pixel_x);
    Serial.print(" ");
    Serial.println(pixel_y);
    */
  }
  return pressed;
}
