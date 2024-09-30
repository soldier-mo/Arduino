#include <IRremote.hpp>

const int pin = 6;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(pin,ENABLE_LED_FEEDBACK);
}

void loop(){
  if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}
