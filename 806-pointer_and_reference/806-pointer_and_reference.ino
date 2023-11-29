void setup() {
  Serial.begin(9600);

  //puntatore
  int num = 0;
  int *pn = &num;

  *pn = 123;
  Serial.print("num: ");Serial.print(num);
  Serial.print("\tpn: ");Serial.println(*pn);

  //reference
  int var = 0;
  int &rv = var;

  var = 12;
  rv = 234;

  Serial.print("var: ");Serial.print(var);
  Serial.print("\t rv: ");Serial.println(rv);



  

}

void loop() {
  // put your main code here, to run repeatedly:

}
