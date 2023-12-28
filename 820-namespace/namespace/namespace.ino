namespace geometria {
  int x, y;
  int z;
}

namespace algebra {
  int x, y;
  int z;
}

namespace complessi {
  int za, zb;
}

using namespace complessi;
using geometria::z;

void setup() {
  Serial.begin(9600);
  geometria::x = 12;
  Serial.print("x da namespace geometria: ");Serial.println(geometria::x); 
  algebra::x = 23;
  Serial.print("x da namespace algebra: ");Serial.println(algebra::x);
  za = 45;
  zb = 56;
  Serial.print("z: ");Serial.print(za);Serial.print("+");Serial.print(zb);Serial.println("i"); 
  geometria::z = 99;
  Serial.print("z da geometria senza ns: ");Serial.println(z);

  {
    using namespace geometria;
    Serial.print("x da namespace geometria: ");Serial.println(x);
  }

  {
    using namespace algebra;
    Serial.print("x da namespace algebra: ");Serial.println(x);
  }
}

void loop() {
  
}
