/*
   scheda: DOIT ESP32 dev kit
   AZDelivery - https://amzn.to/3GwypiZ
   Fare UPLOAD e poi premere il tasto RST sulla scheda

   URL per config schede: https://dl.espressif.com/dl/package_esp32_index.json

   PWM led sul pin 2

   https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html

*/
int pwmchannel = 0; //da 0 a 15
int bit_res = 8;
int freq = 5000; //max 40Mhz!
  
void setup() {
  //setup canale PWM
  ledcSetup(pwmchannel, freq, bit_res);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(2, pwmchannel);
  //posso collegare altri pin allo stesso segnale
  //ledcAttachPin(4, pwmchannel);
}

void loop() {
  for (int i = 0; i < 255; i++) {
    //analogWrite(2, i);
    ledcWrite(pwmchannel, i);
    delay(5);
  }
  for (int i = 255; i >= 0; i--) {
    //analogWrite(2, i);
    ledcWrite(pwmchannel, i);
    delay(5);
  }
}
