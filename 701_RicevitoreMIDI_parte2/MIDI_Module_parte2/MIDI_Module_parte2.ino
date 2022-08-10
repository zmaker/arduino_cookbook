/*
 * https://www.itimarconinocera.org/sito/menu/dipartimenti/tecnico_scientifico_informatica/corso_musica_elettronica/16.htm
 * 
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    A3 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int notes[13] = {
  261,277,293,311,329,
  349,369,392,415,440,
  466,493,523
};

void setup() {
  Serial.begin(31250);

  pinMode(6, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
  display.display();

}

int bc = 0;
byte buff[10];
char str[20];

void loop() {
  while (Serial.available()){
    byte n = Serial.read();
    buff[bc] = n;
    bc++;
  }
  if (bc >= 3) {
    bc = 0;
    display.clearDisplay();
    display.setCursor(0,0);
    sprintf(str, "%d %d %d", buff[0], buff[1], buff[2]);
    display.print(str);

    //pitch 
    int pitch = buff[1];
    int freq = 0;
    if ((pitch >= 60) && (pitch <= 72)) {
      freq = notes[pitch-60];
      display.setCursor(0,30);
      display.print(freq);
    }

    //nota on/off
    display.setCursor(40,10);
    int nota = (buff[0] >> 4);
    if (nota == 9) {
      tone(6, freq);
      display.print("ON");
    } else if (nota == 8) {
      display.print("OFF");
      noTone(6);
    } else {
      display.print("??");
    }

    //ch midi
    display.setCursor(0,10);
    byte ch = getChannel(buff[0]);
    sprintf(str, "CH: %d", ch);
    display.print(str);

    //vel
    int vel = buff[2];
    display.fillRect(0,20, vel,5, SSD1306_WHITE);
    
    display.display();
  }

}

byte getChannel(byte reg) {
  byte n = (int)(reg & B00001111);
  return n;  
}
