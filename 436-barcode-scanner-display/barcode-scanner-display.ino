//RTCLib by Adafruit x DS1307
#include "RTClib.h"
#include <SoftwareSerial.h>

SoftwareSerial scanner(3, 2); // RX, TX

#include <U8x8lib.h>
#define RST_PIN 4
U8X8_SSD1306_128X64_ALT0_HW_I2C oled(U8X8_PIN_NONE); 

void setup () {
  Serial.begin(9600);
  scanner.begin(9600); 
  
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(500);
  digitalWrite(RST_PIN, HIGH);
  oled.begin();
  oled.setFont(u8x8_font_5x7_f);
  oled.setCursor(0,0);    
  oled.print("BarCode Scanner");
  delay(1000);
  oled.clear();  
  oled.setCursor(0,0);    
  oled.print("Wait...");
}

int i = 0;
char code[30];

void loop () {
  if (scanner.available()) {
    char c = scanner.read();
    if (c == '\r') {
      //..
    } else if (c == '\n') {
      i = 0;
      Serial.println(code);
      process(code);
      delay(2000);
      oled.clear();
    } else {
      code[i] = c;
      i++;
    }    
  }
}

void process(char code[]){
  oled.setCursor(0,0);    
  oled.print(code);  
  if (compare(code, "4012700301178")) {
    oled.setCursor(0,1);    
    oled.print("2.00 E");
  } else {
    oled.setCursor(0,1);    
    oled.print("???? E");
  }
}

bool compare(char a[], char b[]) {
  bool ret = false;
  if (sizeof(a) != sizeof(b)) {
    Serial.println("a div b");
    return ret;  
  } else {
    int j = 0;
    while ((a[j] == b[j]) && (j < sizeof(a))) {
      j++;
    }
    if (j < sizeof(a)) {
      ret = false; 
    } else {
      ret = true;
    }    
  }
  return ret;
}
