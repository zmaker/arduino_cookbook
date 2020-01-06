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
const int TS_LEFT=63,TS_RT=766,TS_TOP=508,TS_BOT=638;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

void setup() {
  int id = tft.readID();
  tft.begin(id);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);

  on_btn.initButton(&tft, 60,200, 100,40, WHITE, CYAN, BLACK, "ON", 2);
  off_btn.initButton(&tft, 180,200, 100,40, WHITE, CYAN, BLACK, "OFF", 2);
  on_btn.drawButton(false);
  off_btn.drawButton(false);

  tft.fillRect(40, 80, 160, 80, RED);
}

int pixel_x, pixel_y;

void loop() {
  bool down = getPoint();
  on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
  off_btn.press(down && off_btn.contains(pixel_x, pixel_y));

  if (on_btn.justPressed()) {
    on_btn.drawButton(true);
    tft.fillRect(40, 80, 160, 80, GREEN);
  }

  if (off_btn.justPressed()) {
    off_btn.drawButton(true);
    tft.fillRect(40, 80, 160, 80, RED);
  }

  if (on_btn.justReleased()) {
    on_btn.drawButton(false);
  }
  if (off_btn.justReleased()) {
    off_btn.drawButton(false);
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
  }
  return pressed;
}
