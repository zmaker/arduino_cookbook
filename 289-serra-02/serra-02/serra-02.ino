#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_LAMP 3

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// real time clock
DS1307 rtc;

unsigned long t1, dt1, t2, dt2;

int th1_luce = 80;
int th2_luce = 60;

int mm, hh;
bool GIORNO;
bool LAMP;

int luce = 0;

//icona sole
static const unsigned char PROGMEM logo8_sun_bmp[] =
{ B00010000, 
  B01000010,
  B00011000, 
  B00111101,
  B10111100, 
  B00011000,
  B01000010, 
  B00001000 };

static const unsigned char PROGMEM logo8_moon_bmp[] =
{ B00011100, 
  B00110010,
  B01100000, 
  B11100000,
  B11100000, 
  B01100000,
  B00110010, 
  B00011100 };

 static const unsigned char PROGMEM logo8_light_bmp[] =
{ B00011000, 
  B01100110,
  B10000001, 
  B10011001,
  B01000010, 
  B00111100,
  B00100100, 
  B00011000 };
  
void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  if (!rtc.begin()) {
    Serial.println("Errore! Verifica le connesioni dell'RTC!");
    return;
  }
  if (!rtc.isrunning()) {
    Serial.println("Configuro l'ora");
    //Uso l'ora di compilazione dello sketch
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // per farlo a mano...
    // January 21, 2014 at 3am you would call
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  display.setTextSize(1);      
  display.setTextColor(WHITE); 
  display.cp437(true);
  display.clearDisplay();  
  
  pinMode(PIN_LAMP, OUTPUT);  //luce
  leggiOra();
  leggiLuce();
}

void loop() {
  /**
   * TIMER
   */
  dt1 = millis() - t1;
  if (dt1 >= 2000) {
    t1 = millis();
    leggiLuce();
    leggiOra();
  }
  dt2 = millis() - t2;
  if (dt2 >= 200) {
    t2 = millis();
    aggiornaDisplay(luce); 
  }

  //applico le azioni
  digitalWrite(PIN_LAMP, LAMP);
  
}

void leggiLuce() {
  for (int i = 0; i < 10; i++) {
    luce += analogRead(A0);
  }
  luce = luce / 10;
  luce = map (luce, 0, 1024, 0, 100);
    
  if (GIORNO) {  
    if (luce > th1_luce) {
      LAMP = LOW;
    } else if (luce < th2_luce) {
      LAMP = HIGH;
    }
  }
}

void leggiOra(){
  DateTime now = rtc.now();
  hh = now.hour();
  mm = now.minute();  
  
  if ((hh >= 6) && (hh < 22)) {
    GIORNO = true;
  } else {
    GIORNO = false;  
  }
  
}

void aggiornaDisplay(int luce) {
  display.clearDisplay();  
  
  //ore e minuti
  display.setCursor(0, 0);              
  display.print(hh);
  display.print(":");
  display.print(mm);    
  
  display.setCursor(0, 20);              
  display.print(luce);
  display.print("%");
  if (GIORNO) {
    display.drawBitmap(30, 0,  logo8_sun_bmp, 8, 8, 1); 
  } else {
    display.drawBitmap(30, 0,  logo8_moon_bmp, 8, 8, 1); 
  }
  if (LAMP) {
    display.drawBitmap(0, 30,  logo8_light_bmp, 8, 8, 1);               
  }
  
  display.display(); 
}
