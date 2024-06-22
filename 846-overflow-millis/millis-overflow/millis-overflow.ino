void setup() {
  Serial.begin(9600);
  Serial.println("\noverflow");
  
  Serial.print("2^1: ");Serial.println(pow2(1));
  Serial.print("2^2: ");Serial.println(pow2(2));
  Serial.print("2^4: ");Serial.println(pow2(4));

  unsigned long t = pow2(32) - 1;
  Serial.print("2^32 - 1: ");Serial.println(t);
  Serial.print("2^32: ");Serial.println(pow2(32));

  //if (millis() > t1 + 2000)
  unsigned long milli = pow2(32) - 1;
  unsigned long t1 = milli;
  Serial.println("millis() > \tt1 \t+ \t2000 ");
  Serial.print(milli);Serial.print("\t");Serial.print(t1);Serial.print("\t");
  Serial.print(2000);Serial.println(" ");
  milli += 10;
  Serial.print(milli);Serial.print("\t\t");Serial.print(t1);Serial.print("\t");
  Serial.print(2000);Serial.println(" ");

  //if (millis() - t1 > 2000)
  milli = pow2(32)-1;
  t1 = milli;
  Serial.println("\nmillis() - t1  > 2000 ");
  unsigned long dt = milli - t1;
  Serial.print(dt);Serial.print("\t\t");
  Serial.print(2000);Serial.println(" ");
  milli += 10;
  dt = milli - t1;
  Serial.print(dt);Serial.print("\t\t");
  Serial.print(2000);Serial.println(" ");

}

void loop() {
}

unsigned long pow2(int exp){
  unsigned long ret = 1;
  for (int i = 0; i < exp; i++){
    ret *= 2;
  }
  return ret;
}