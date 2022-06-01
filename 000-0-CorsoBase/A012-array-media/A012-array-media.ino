int lux[10];
int temp[] = {12,23,34,45,56};

void setup() {
  Serial.begin(9600); 

  int n = sizeof(temp) / sizeof(int);
  Serial.println(n);

  for (int i = 0; i < (sizeof(lux) / sizeof(int)); i++) {
    lux[i] = 0;
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lux[i]);
  }

  for (int i = 0; i < (sizeof(temp) / sizeof(int)); i++) {    
    Serial.print(i);
    Serial.print(": ");
    Serial.println(temp[i]);
  }
  
}

void loop() {
  for (int i = 0; i < 10; i++) {
    lux[i] = analogRead(A0);
    Serial.print(lux[i]);
    Serial.print("\t");
  }
  Serial.print("\n");

  float media = 0.0;
  float somma = 0.0;
  for (int i = 0; i < 10; i++) {
    somma = somma + (float)lux[i]; 
  }
  Serial.print("somma: ");
  Serial.println(somma);
  media = somma / 10.0;
  Serial.print("media: ");
  Serial.println(media);
  delay(1000);
}
