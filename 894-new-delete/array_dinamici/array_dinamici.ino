int *arr;
int size = 3;

void setup() {
  pinMode(2, INPUT);

  Serial.begin(9600);

  arr = new int[size];

  //init
  for (int i = 0; i < size; i++){
    arr[i] = 0;
  }
  
  //delete[] arr;
  
}

void loop() {
  if (digitalRead(2)) {
    Serial.println("Add data");
    //puoi simulare l'aumento della dimensione creando un nuovo 
    //array più grande, copiando i dati dal vecchio array e poi 
    //deallocando la memoria del vecchio array.

    size++;
    // Creazione di un array più grande
    int* temparr = new int[size];
    //copio
    for (int i = 0; i < size-1; i++) {
        temparr[i] = arr[i];
    }
    //elimino il vecchio array
    delete[] arr;
    //riassegno
    arr = temparr;

    //memorizzo lettura
    arr[size-1] = analogRead(A0);

    //stampo i dati
    for (int i = 0; i < size; i++) {
        Serial.print(arr[i]); 
        Serial.print(" "); 
    }
    Serial.println(""); 
    
    delay(300);
  }

}
