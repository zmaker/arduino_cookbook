class Test {
  private:
    static int instances;
  public:
    Test(int n = 0);
    ~Test();
    int temp;
    int getI();
};

int Test::instances = 0;

Test::Test(int n = 0){ 
  temp = n;
  instances++;
}

Test::~Test(){
  instances--;
}

int Test::getI(){
  return instances;
}

void setup() {
  Serial.begin(9600);
  Test t1 = Test(1);
  Test t2 = Test(12);
  Test t3 = Test(34);
  Serial.print("t1: ");Serial.print(t1.temp);Serial.print(" i: ");Serial.println(t1.getI());
  Serial.print("t2: ");Serial.print(t2.temp);Serial.print(" i: ");Serial.println(t2.getI());
  Serial.print("t3: ");Serial.print(t3.temp);Serial.print(" i: ");Serial.println(t3.getI());
}

void loop() {
  // put your main code here, to run repeatedly:

}
