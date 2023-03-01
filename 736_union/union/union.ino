union mixed {
  byte buff[2];
  unsigned int n;  
};

void setup() {
  Serial.begin(9600);

  union mixed var;
  var.buff[0] = 0xD2;
  var.buff[1] = 0x04;

  Serial.print("n: ");Serial.println(var.n);

  var.n = 258; 
  Serial.print("A: ");Serial.println(var.buff[0]);
  Serial.print("B: ");Serial.println(var.buff[1]);

}

void loop() {
  // put your main code here, to run repeatedly:

}
