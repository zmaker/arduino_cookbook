int valori[10];

void setup() {
 Serial.begin(9600);

 for (int i = 0; i < 10; i++){
   valori[i] = analogRead(A0); 
 }

 float media = 0.0;
 for (int i = 0; i < 10; i++){
   media += valori[i];
 }
 media = media / 10.0;
 Serial.println(media);
}

void loop() {
  // put your main code here, to run repeatedly:

}
