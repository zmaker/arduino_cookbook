/* 
Autore: Paolo Aliverti
Listato 7.26 – Client BLE - si collega al serve e legge il valore pubblciato
*/
#include "BLEDevice.h"

//Il nome del servizio/dispositivo BLE a cui collegarsi
#define bleServerName "ESP32 BLE Server"

//servizio batteria e livello di carica
static BLEUUID batteryServiceUUID("0000180F-0000-1000-8000-00805F9B34FB");
static BLEUUID battLevelCharacteristicUUID("00002A19-0000-1000-8000-00805F9B34FB");

//Flag di stato:
static boolean IN_CONNESSIONE = false; //il dispositivo deve connettersi
//static boolean CONNECTED = false; //il dispositivo è connesso

//Indirizzo del dispositivo a cui collegarsi
static BLEAddress *bleServerAddress;
 
//caratteristica da leggere
static BLERemoteCharacteristic* chBatteria;

//Attivazione notifiche
const uint8_t notificationOn[] = {0x1, 0x0};
const uint8_t notificationOff[] = {0x0, 0x0};

//livello batteria
uint8_t* battery_level;
boolean UPDATED = false;

//Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) {
   BLEClient* pClient = BLEDevice::createClient();
 
  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");
 
  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(batteryServiceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Servizio UUID non trovato");    
    return (false);
  }
 
  // Obtain a reference to the characteristics in the service of the remote BLE server.
  chBatteria = pRemoteService->getCharacteristic(battLevelCharacteristicUUID);
  
  if (chBatteria == nullptr ) {
    Serial.print("Caratteristica non trovata");
    return false;
  }

  chBatteria->registerForNotify(batteryNotifyCallback);
  return true;
}

class AdvertiseReceived: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == bleServerName) { //i nomi coincidono
      //fermo lo scan
      advertisedDevice.getScan()->stop(); 
      //recupero l'indirizzo del server (advertiser)
      bleServerAddress = new BLEAddress(advertisedDevice.getAddress()); 
      IN_CONNESSIONE = true;
      Serial.println("Server trovato: in connessione");
    }
  }
};
 
static void batteryNotifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic, 
  uint8_t* pData, size_t length, bool isNotify) {
  
  battery_level = (uint8_t*)pData;
  UPDATED = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("BLE Client");

  BLEDevice::init("");
 
  //server uno scanner per cercare il server
  BLEScan* pBLEScan = BLEDevice::getScan();
  //funziona callback per lo scanner
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertiseReceived());
  //avvio lo scanner per 30 secofni
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  if (IN_CONNESSIONE == true) {
    if (connectToServer(*bleServerAddress)) {
      Serial.println("Connesso al server BLE");
      //richiedeo di essere notificato per la caratteristica che mi interessa
      chBatteria->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);      
    } else {
      Serial.println("Connessione fallita");
    }
    IN_CONNESSIONE = false;
  }
  
  if (UPDATED){
    //ricevo valori
    Serial.print("batteria: ");
    Serial.print(*battery_level);
    Serial.println("%");
    UPDATED = false;
  }
  delay(1000);
}
