void setup() {
  Serial.begin(9600);
  
  sayHello();
  sayHello("Paolo");

  int n = somma(10, 15);
  Serial.println(n);
}

void loop() {
  switch(stato){
    case 0:
      //codice di gestione del caso 0
      inizializzazione();
    break; 
    case 1:
      //codice di gestione del caso 1
      letturaValori();
    break; 
    case 2:
      //codice di gestione del caso 2
      scritturaRisultati();
    break; 
  }
}

void inizializzazione(){
  
  }

void sayHello(){
  Serial.println("hello");
}

void sayHello(String nome){
  Serial.print("hello ");
  Serial.println(nome);
}

int somma(int n, int m){
  int res = n + m;
  return res;  
}



