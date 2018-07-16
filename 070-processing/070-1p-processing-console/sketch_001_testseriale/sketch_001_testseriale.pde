import processing.serial.*;

Serial myPort;  

void setup() {   
  //scan delle porte
  for (int i = 0; i < Serial.list().length; i++) {
    print(i + " ");
    println(Serial.list()[i]);
  }  
  String portName = Serial.list()[2]; //correggere con l'id della vs porta
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  if ( myPort.available() > 0) {  
    // se ci sono dati...
    String val = myPort.readStringUntil('\n');  // leggili
    println(val); //stampali
  } 
  
}