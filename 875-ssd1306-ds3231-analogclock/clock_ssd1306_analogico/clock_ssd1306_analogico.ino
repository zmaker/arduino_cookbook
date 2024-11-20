#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 3D o 3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTCLib - Neiro
#include <RTClib.h>
DS3231 rtc;

// buffer for DateTime.tostr
char buf[20];

int bt1, bt2, pv_bt1, pv_bt2;
unsigned long t1, t2;
int stato = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  rtc.begin();
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if ((millis() - t1) > 500) {
    t1 = millis();
    DateTime now = rtc.now();
    int hh = now.hour();
    int mi = now.minute();

    display.clearDisplay();
    clock(hh, mi);
    display.display();

    Serial.print(hh);
    Serial.print(":");
    Serial.println(mi);
  }
  
  bt1 = !digitalRead(2);
  bt2 = !digitalRead(3);

  switch(stato){
    case 0:
    runclock();
    break;
    case 1:
    sethours();
    break;
    case 2:
    setminutes();
    break;
  }
  
  pv_bt1 = bt1;
  pv_bt2 = bt2;
}

void runclock(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt1...");
  }
  if (!bt1 && pv_bt1) { //FDD
    if ((millis() - t2) > 2000) {
      Serial.println("set");
      stato = 1;
    }
  }
}

void sethours(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt1->setmin");
    delay(300);
    stato = 2;
  }
  if (bt2 && !pv_bt2) { //FDS
    Serial.println("h+");
    DateTime now = rtc.now();    
    int hh = now.hour()+1;
    if (hh >= 24) hh = 0;
    DateTime dt0(now.year(), now.month(), now.day(), hh, now.minute(), now.second());
    rtc.adjust(dt0);
  }
}

void setminutes(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt1->run");
    delay(300);
    stato = 0;
  }
  if (bt2 && !pv_bt2) { //FDS
    Serial.println("m+");
    DateTime now = rtc.now();    
    int mi = now.minute()+1;
    if (mi >= 60) mi = 0;
    DateTime dt0(now.year(), now.month(), now.day(), now.hour(), mi, now.second());
    rtc.adjust(dt0);
  }
}

void clock(int hh, int mm) {
  const float r = (SCREEN_HEIGHT/2) - 5;
  const float rh = (SCREEN_HEIGHT/2) * 0.5;
  const float rm = (SCREEN_HEIGHT/2) * 0.8;

  float a = 0;
  //ore
  a = (6.28/12.0) * (float)hh;
  int xh = SCREEN_WIDTH/2 + rh*sin(a);
  int yh = SCREEN_HEIGHT/2 - rh*cos(a);
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xh, yh, SSD1306_WHITE);
  //min
  a = (6.28/60.0) * (float)mm;
  int xm = SCREEN_WIDTH/2 + rm*sin(a);
  int ym = SCREEN_HEIGHT/2 - rm*cos(a);
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xm, ym, SSD1306_WHITE);
  //corona
  for (int i = 0; i < 360; i = i + 15) {
    a = ((float)i * 3.14) / 180.0;
    int xp = SCREEN_WIDTH/2 + r*sin(a);
    int yp = SCREEN_HEIGHT/2 - r*cos(a);
    if (i%30) {
      display.drawPixel(xp, yp, SSD1306_WHITE);
    } else {
      display.fillCircle(xp, yp, 1, SSD1306_WHITE);
    }
  }
} 