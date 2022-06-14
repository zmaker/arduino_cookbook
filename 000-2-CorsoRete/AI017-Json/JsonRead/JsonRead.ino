// ArduinoJson - https://arduinojson.org
#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  
  //apri la seriale per iniziare
  while (!Serial) continue;

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the capacity of the memory pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use https://arduinojson.org/v6/assistant to compute the capacity.
  //StaticJsonDocument<200> doc;

  // StaticJsonDocument<N> allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  // https://www.javatpoint.com/stack-vs-heap-java#:~:text=The%20major%20difference%20between%20Stack,dynamic%20memory%20allocation%20and%20deallocation.
  DynamicJsonDocument doc(200);

  // JSON input string.
  //
  // Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
  // the minimal amount of memory because the JsonDocument stores pointers to
  // the input buffer.
  // If you use another type of input, ArduinoJson must copy the strings from
  // the input to the JsonDocument, so you need to increase the capacity of the
  // JsonDocument.  
/*
{ "nome":"Paolo", "eta":23, "hobby":{"arduino":true, "sport":"running", "cooking":false},
"corsi":["elettronica","CAD","math"]
}
*/
  char json[] = "{ \"nome\":\"Paolo\", \"eta\":23, \"hobby\":{\"arduino\":true, \"sport\":\"running\", \"cooking\":false}, \"corsi\":[\"elettronica\",\"CAD\",\"math\"] }";
  Serial.println(json);
  
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    //in caso di errori vedere:
    //https://jsonformatter.curiousconcept.com/#
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  const char* nome = doc["nome"];
  Serial.println(nome);
  int eta = doc["eta"];
  Serial.println(eta);
  bool hobby = doc["hobby"]["arduino"]; 
  Serial.println(hobby);
  const char* corso = doc["corsi"][1];    
  Serial.println(corso);
  
}

void loop() {
  
}
