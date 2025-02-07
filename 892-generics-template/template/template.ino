template <typename T>
T sum (T a, T b) {
  return a+b;
}

template <typename T>
void prtv(String msg, T val) {
  Serial.print(msg);Serial.print(": ");Serial.println(val);
}
template <>
void prtv<double>(String msg, double val) {
  Serial.print(msg);Serial.print(": ");Serial.println(val, 3);
}
template <>
void prtv<String>(String msg, String val) {
  Serial.print(msg);Serial.print(": '");Serial.print(val);Serial.println("'");
}

void setup() {
  Serial.begin(9600);
  int n = sum<int>(10, 23);
  //int n = sum(10, 23);
  Serial.print("n: ");Serial.println(n);
  float f = sum<float>(12.3f, 34.5f);
  Serial.print("f: ");Serial.println(f);

  prtv<int>("t", 12);
  prtv<float>("h", 12.3f);
  prtv<double>("x", 23.456);
  prtv<String>("name", "Mario");
}

void loop() {
  // put your main code here, to run repeatedly:

}
