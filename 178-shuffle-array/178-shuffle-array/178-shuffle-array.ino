byte pins[5] = {2, 3, 4, 5, 6};
byte result[5];

byte temp[5];

int i = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  int osize = 5;

  for (int k = 0; k < 5; k++) {
    int p = random(osize);
    int estratto = pins[p];
  
    result[i] = estratto;
    i++;
  
    int ti = 0;
    for (int n = 0; n < osize; n++) {    
      if (n != p) {
        temp[ti] = pins[n];
        ti++;
      }    
    }
    osize--;
    for (int x = 0; x < 5; x++) {    
      if (x < osize) {
        pins[x] = temp[x];  
      } else {
        pins[x] = 0;
      } 
    }
  }

  //stampo result x verifica
  for (int x = 0; x < 5; x++) {    
     Serial.println(result[x]);    
  }
  
}

void loop() {}
