#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

char *name = "My LCD";
const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
const int TS_LEFT=98,TS_RT=918,TS_TOP=75,TS_BOT=888;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

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

void setup() {
  Serial.begin(9600);
  int id = tft.readID();
  if (id == 0xD3D3) id = 0x9486; 
  tft.begin(id);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  
}

void loop() {
  tp = ts.getPoint();

  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);
  digitalWrite(XM, HIGH);
  
  if ((tp.z > MINPRESSURE) && (tp.z < MAXPRESSURE)) {
    int px = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
    int py = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    Serial.print(tp.x);
      Serial.print("\t");
      Serial.print(tp.y);
      Serial.print("\t");
      Serial.print(tp.z);
      Serial.print("\t");
        Serial.print(px);
        Serial.print("\t");
        Serial.println(py);

    tft.fillCircle(px, py, 5, WHITE);
  }

}
