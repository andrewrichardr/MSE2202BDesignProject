#include <IRremote.h>
#include <IRremoteInt.h>

#define RECV_PIN 7
IRrecv receiver(RECV_PIN);
decode_results results;
unsigned char ledTx; 

void setup() {
  // put your setup code here, to run once:
  receiver.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (receiver.decode(&results)) { 
    Serial.write(ledTx);
    receiver.resume();
  }
}
