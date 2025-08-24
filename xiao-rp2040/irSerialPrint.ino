#define DECODE_NEC            // DECODE_NEC
#include <IRremote.hpp>       // Do not change header order.

constexpr uint8_t RECV_PIN {1};
constexpr uint8_t LED {12};

constexpr uint16_t S1 = 0x38;  // Taste 5

uint16_t irReceive() {
  uint16_t received{0};
  
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    // if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
    //   // We have an unknown protocol here, print more info
    //   IrReceiver.printIRResultRawFormatted(&Serial, true);
    // }
    // if (IrReceiver.decodedIRData.protocol == NEC) {
    //   received = IrReceiver.decodedIRData.command;
    //   Serial.print("Command: 0x");
    //   Serial.println(received, HEX);
    // }
    IrReceiver.resume();
  }
  return received;
}

void setup()
{
  Serial.begin(9600);

  pinMode (LED, OUTPUT); 
  digitalWrite (LED, HIGH);

  IrReceiver.begin(RECV_PIN);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(RECV_PIN);
}

void loop()
{
   if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    // if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
    //   // We have an unknown protocol here, print more info
    //   IrReceiver.printIRResultRawFormatted(&Serial, true);
    // }
    // if (IrReceiver.decodedIRData.protocol == NEC) {
    //   received = IrReceiver.decodedIRData.command;
    //   Serial.print("Command: 0x");
    //   Serial.println(received, HEX);
    // }
    IrReceiver.resume();
  }
}