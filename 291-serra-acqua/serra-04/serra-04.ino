#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_LAMP 3
#define PIN_BED 4
#define PIN_POMPA 5

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// real time clock
DS1307 rtc;

unsigned long t1, dt1, t2, dt2;

unsigned long t4, dt4;
int terra;
int th_terra = 100;
bool POMPA;
int t_on_pompa = 1000;
int statopompa = LOW;

unsigned long t3, dt3;
int tbed;
int th1_bed = 700;
int th2_bed = 660;
bool BED = LOW;
int t_on_bed = 1000;
int statobed = LOW;

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

static const unsigned char PROGMEM logo8_bed_bmp[] =
{ B01010100, 
  B01010100,
  B00101010, 
  B01010100,
  B01010100, 
  B00000000,
  B11111111, 
  B00000000 };

static const unsigned char PROGMEM logo8_water_bmp[] =
{ B00010000, 
  B00010000,
  B00111000, 
  B00111000,
  B01111100, 
  B11111110,
  B01111100, 
  B00111000 };
  
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
  pinMode(PIN_BED, OUTPUT);
  pinMode(PIN_POMPA, OUTPUT);

  digitalWrite(PIN_LAMP, LOW);
  digitalWrite(PIN_BED, LOW);
  digitalWrite(PIN_POMPA, LOW);
    
  leggiOra();
  leggiLuce();
  leggiTemperaturaBed();
  leggiTerra();
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
    leggiTemperaturaBed();
    leggiTerra();
  }
  dt2 = millis() - t2;
  if (dt2 >= 200) {
    t2 = millis();
    aggiornaDisplay(luce); 
  }

  if (BED) {
    dt3 = millis() - t3;
    if (dt3 >= t_on_bed) {
      t3 = millis();
      statobed = !statobed;
      if (statobed) {
        digitalWrite(PIN_BED, HIGH);  
        t_on_bed = 1000;
      } else {
        digitalWrite(PIN_BED, LOW);
        t_on_bed = 3000;
      } 
    }  
  } else {
    digitalWrite(PIN_BED, LOW);
  }

  if (POMPA) {
    dt4 = millis() - t4;
    if (dt4 > t_on_pompa) {
      t4 = millis();
      statopompa = !statopompa;
      if (statopompa) {
        digitalWrite(PIN_POMPA, HIGH);
        t_on_pompa = 1000;
      } else {
        digitalWrite(PIN_POMPA, LOW);
        t_on_pompa = 10000;
      }
    }  
  }

  //applico le azioni
  digitalWrite(PIN_LAMP, LAMP);
  
}

void leggiTerra(){
  terra = 0;
  for (int i = 0; i < 10; i++) {
    terra += analogRead(A1);  
  } 
  terra = terra / 10;

  if (GIORNO) {
    if (terra < th_terra) {
      POMPA = HIGH;
    } else {
      POMPA = LOW;
      digitalWrite(PIN_POMPA, LOW);
    }
  } else {
    POMPA = LOW;
    digitalWrite(PIN_POMPA, LOW);
  }
}

void leggiTemperaturaBed() {
  tbed = 0;
  for (int i = 0; i < 10; i++) {
    tbed += analogRead(A2);  
  }
  tbed = tbed / 10;
  tbed = map(tbed, 0, 1024, 1024, 0);

  if (tbed < th1_bed) {
    BED = HIGH;
  } else if (tbed > th2_bed) {
    BED = LOW;
  }  
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
  } else {
    LAMP = LOW;
    digitalWrite(PIN_LAMP, LOW);
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
  if (BED) {
    display.drawBitmap(40, 0,  logo8_bed_bmp, 8, 8, 1);               
  }
  if (POMPA) {
    display.drawBitmap(50, 0,  logo8_water_bmp, 8, 8, 1);               
  }
  
  display.display(); 
}
