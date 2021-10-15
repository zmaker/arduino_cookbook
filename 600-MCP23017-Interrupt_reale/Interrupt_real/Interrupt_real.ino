// NOTE: This is a simple example that only reads the INTA or INTB pin
//       state. No actual interrupts are used on the host microcontroller.
//       MCP23XXX supports the following interrupt modes:
//           * CHANGE - interrupt occurs if pin changes to opposite state
//           * LOW - interrupt occurs while pin state is LOW
//           * HIGH - interrupt occurs while pin state is HIGH

#include <Adafruit_MCP23X17.h>

volatile bool pressed = false;

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);

  if (!mcp.begin_I2C(0x27)) {
    Serial.println("Error.");
    while (1);
  }

  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), handler, FALLING);

  // OPTIONAL - call this to override defaults
  // mirror INTA/B so only one wire required
  // active drive so INTA/B will not be floating
  // INTA/B will be signaled with a LOW
  mcp.setupInterrupts(true, false, LOW);

  // configure button pin for input with pull up
  mcp.pinMode(1, INPUT);

  // enable interrupt on button_pin
  mcp.setupInterruptPin(1, HIGH);

  Serial.println("Looping...");
}

void handler() {
  pressed = true;  
}

void loop() {
  if (pressed) {
    pressed = false;
    Serial.print("Interrupt detected on pin: ");
    Serial.println(mcp.getLastInterruptPin()); 
    digitalWrite(13, HIGH);
    delay(300); 
    digitalWrite(13, LOW);
  }
}
