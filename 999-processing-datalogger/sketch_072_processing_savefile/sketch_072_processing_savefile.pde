import processing.serial.*;

PrintWriter file;

Serial myPort;  
String val; 

void setup()
{
  for (int i = 0; i < Serial.list().length; i++) {
    print(i + " ");
    println(Serial.list()[i]);
  }  
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  //creo il file di log
  file = createWriter("log.txt"); 
}

void draw() {
  if ( myPort.available() > 0) {  
    // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
    println(val); //print it out in the console
    file.println("rx:"+val);// Finishes the file
    file.flush(); // Writes the remaining data to the file
    file.close();
    delay(100);
  } 
  
}