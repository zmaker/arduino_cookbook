/**
 * Gestisce un LED in PWM per simulare alba e tramonto
 * accende le luci delle case
 * simula un fuoco
 * 
 * sole: pwm pin 5
 * case: pin 4
 * fuoco: pwm pin 6
 * 
 * con mp3 player (dfminiplayer)
 * collegato sui pin:
 * 10 rx <- tx player 
 * 11 tx -> rx player
 * 
 *  neopixel su pin 7
 */
#include <FastLED.h>
#define NUM_LEDS 16
CRGB leds[NUM_LEDS];
int h = 0;
int s = 255;

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial sSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int trid = 0;
#define MAXTRACKS 4
int tracks[] = {1,3,5,7};

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
    
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  
  sSerial.begin(9600);
  while (!sSerial) delay(1);
  Serial.println(F("Presepe V2.0"));

  if (!myDFPlayer.begin(sSerial)) {
    Serial.println(F("Error"));
    while(true);
  }
  Serial.println(F("ready!"));
  myDFPlayer.volume(30);

  delay(1000);
  myDFPlayer.play(tracks[0]);
  trid++;
}

unsigned long tc, t1, t2;

void loop() {
  tc = millis();
  if ((tc - t1) > 60000) {    
    //Serial.print("t1: ");
    //Serial.println(t1);
    t1 = millis();
  }
  
  if ((tc - t2) > 100) {   
     
    //alba
    taskPwm(6, tc-t1, 0, 6000, 0, 255);  
    //giorno
    taskPin(6, tc-t1, 6000, 24000, HIGH);  
    //tramonto
    taskPwm(6, tc-t1, 24000, 34000, 255, 0);   
    //notte
    taskPin(6, tc-t1, 34000, 60000, LOW);  

    //neopixel
    //alba
    taskNPAlba1(tc-t1, 0, 3000);
    taskNPAlba2(tc-t1, 3000, 6000);
    //giorno
    taskNPGiorno(tc-t1, 6000, 24000);
    //tramonto
    taskNPTramonto1(tc-t1, 24000, 26000);
    taskNPTramonto2(tc-t1, 26000, 29000);
    taskNPTramonto3(tc-t1, 29000, 34000);
    //notte
    taskNPNotte(tc-t1, 34000, 60000);

    //accende e spegne le case
    taskPin(4, tc-t1, 0, 3000, HIGH);
    taskPin(4, tc-t1, 3000, 28000, LOW);  
    taskPin(4, tc-t1, 28000, 60000, HIGH);

    //il fuoco
    fuoco(5);

    //musica
    music();

    //Serial.println(tc-t1);
    t2 = millis();
  } 
}

void taskPwm(int pin, unsigned long t, unsigned long t1, unsigned long t2, int l1, int l2){
  if (t >= t1 && t < t2) {
    int pwm = map(t-t1, 0, t2-t1, l1, l2);
    analogWrite(pin, pwm);
  }
}

void taskPin(int pin, unsigned long t, unsigned long t1, unsigned long t2, int stato){
  if (t >= t1 && t < t2) {
    digitalWrite(pin, stato);    
  }
}

void fuoco(int pin){
  analogWrite(pin, random(256)); 
}

void music() {
  //suona una dopo l'altra le tracce presenti sulla sdcard  
  int st = myDFPlayer.readState();
  //Serial.println(st);
  //513 è in play
  //512 ha finito
  if ( (st == 512)) {
    //ha terminato
    myDFPlayer.play(tracks[trid]);
    Serial.print("track: ");
    Serial.println(tracks[trid]);
    trid++;
    if (trid >= MAXTRACKS) trid = 0;  
  } else if (st == 513) {
    //playing...
  }
}


void taskNPAlba1(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    h = map(t-t1, 0, t2-t1, 160, 200);
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
  }
}
void taskNPAlba2(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    s = map(t-t1, 0, t2-t1, 255, 0);
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
  }
}
void taskNPGiorno(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    h = 64; //giallo
    s = 0;
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
  }
}
void taskNPNotte(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    h = 160; //giallo
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
  }
}
void taskNPTramonto1(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    s = map(t-t1, 0, t2-t1, 0, 255);
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
  }
}
void taskNPTramonto2(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    h = map(t-t1, 0, t2-t1, 64, 0);
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
  }
}
void taskNPTramonto3(unsigned long t, unsigned long t1, unsigned long t2){
  if (t >= t1 && t < t2) {
    h = map(t-t1, 0, t2-t1, 255, 60);
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
  }
}
