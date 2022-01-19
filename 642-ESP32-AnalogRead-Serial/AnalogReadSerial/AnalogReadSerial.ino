/*
 * Info: 
 * https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
 */
/*
 * scheda: DOIT ESP32 dev kit
 * AZDelivery - https://amzn.to/3GwypiZ
 * Fare UPLOAD e poi premere il tasto RST sulla scheda
 * 
 * URL per config schede: https://dl.espressif.com/dl/package_esp32_index.json
 * 
 * Potenziometro su pin 34 (adc ch6) e led su pin 2 (pwm)
 * 
 */
int pwmchannel = 0; //da 0 a 15
int bit_res = 12;
int freq = 5000; //max 40Mhz!

void setup() {
  //setup canale PWM
  ledcSetup(pwmchannel, freq, bit_res);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(2, pwmchannel);

  Serial.begin(9600);
}
 
void loop() {
  int v = analogRead(34);
  ledcWrite(pwmchannel, v);
  Serial.println(v);
  delay(100);
  
}
