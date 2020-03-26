#include <Servo.h>  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo myservo;      
int Echo = 8;  
int Trig = 9; 

void setup() {
  myservo.attach(3);
  Serial.begin(9600);    
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);   
  Serial.println("Ok");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay(); 
}

void loop() {
  Serial.println("Scan");
  display.clearDisplay();    
  myservo.write(90);
  for (int i = 30; i < 150; i = i + 5) {
    myservo.write(i);
    int d = readDistanza();
    d = map(d, 0, 100, 0, 60);

    float a = PI * (float)i / 180.0f;

    int xl = 64 - cos(a) * d;
    int yl = 10 + sin(a) * d;
    
    display.drawLine(64, 10, xl, yl, WHITE);
    display.display();
    delay(100);
    Serial.println(d);
  }
  myservo.write(90);
  delay(500);
}

int readDistanza() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float d = pulseIn(Echo, HIGH);  
  d = d / 58;       
  return (int)d;
}  
