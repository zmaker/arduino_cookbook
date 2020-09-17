import processing.serial.*;

Serial myPort;
String val;

void setup() {
 size(300, 200);
 background(30, 121, 175);
 stroke(255);
 
 String[] seriali = Serial.list();
 for(int i = 0; i < seriali.length; i++){
  println(i + ") " + seriali[i]);
 }
 String portName = Serial.list()[3];
 myPort = new Serial(this, portName, 115200);
 
}

void draw() {
 if (myPort.available() > 0){
  val = myPort.readStringUntil('\n');

  if (val != null) {
   String[] tk = splitTokens(val, ";");
   int[] n = new int[tk.length];
   background(30, 121, 175);
   
   for (int i = 0; i < 128; i++){
    if((tk[i] != null) && (tk[i].length() > 0)){
      try {
       n[i] = Integer.parseInt(tk[i]);
      } catch (Exception e){
       n[i] = 0;
      }
      
      float xp = map(i, 0, 128, 10, width-10);
      float yp = map(n[i], 0, 1024, height-10, 10);
      point(xp, yp);
    }
   }
   
  }
 }
}
