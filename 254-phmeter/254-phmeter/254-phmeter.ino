/*
 * Video 254 ARduino - ph sensor
https://www.dfrobot.com/product-1025.html
*/

void setup() {
  Serial.begin(9600);  
  Serial.println("PH meter");
}

float misura;

void loop() {
  for(int i=0; i<10; i++) { 
    misura += analogRead(A0);
    delay(10);
  }

  misura = misura / 10.0;  
  float ph = (float)misura * (5.0/1024);
  Serial.println(ph);
  ph = 3.3 * ph;  
  Serial.print("    pH:");  
  Serial.print(ph, 2);
  Serial.println(" ");
  delay(1000);

}
