int n = 123;
float d = 1.23;

char str[100];

void setup() {  
  Serial.begin(9600);
  int caratteri_scritti = sprintf(str, "%05d", n);  
  Serial.println(str);
  
  sprintf(str, "formattato: %05d char: %d", n, caratteri_scritti);
  Serial.println(str);

  sprintf(str, "formattato: %05d char: %d", n, caratteri_scritti);
  Serial.println(str);

  //non va con arduino!!
  sprintf(str, "%f", d);
  Serial.println(str);


  dtostrf(d, 5,4, str);  //numero, lunghezza della stringa che sarà creata, num decimali
  Serial.println(str);

  dtostrf(d, 10,2, str);
  Serial.println(str);

  dtostrf(d, 10,2, str);
  Serial.println(str);

  dtostrf(-d, 10,2, str);
  Serial.println(str);
}

void loop() {
  // put your main code here, to run repeatedly:

}
