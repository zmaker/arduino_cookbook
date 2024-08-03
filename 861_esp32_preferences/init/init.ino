#include <nvs_flash.h>

//https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/

void setup() {
  Serial.begin(115200);
  delay(3000);
  nvs_flash_erase(); // erase the NVS partition and...
  Serial.println("NVM: erased");
  nvs_flash_init(); // initialize the NVS partition.
  Serial.println("NVM: formatted");
}

void loop() {

}