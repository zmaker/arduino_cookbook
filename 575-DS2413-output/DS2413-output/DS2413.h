#define DS2413_FAMILY_ID    0x3A
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF

bool write(OneWire oneWire, uint8_t address[8], uint8_t stato){
  uint8_t ack = 0;
  stato |= 0xFC;
  
  oneWire.reset();
  oneWire.select(address);
  oneWire.write(DS2413_ACCESS_WRITE);
  oneWire.write(stato);
  oneWire.write(~stato);
  ack = oneWire.read();
  if (ack == DS2413_ACK_SUCCESS) {
    oneWire.read();
  }
  oneWire.reset();
  return (ack == DS2413_ACK_SUCCESS ? true : false);
}
