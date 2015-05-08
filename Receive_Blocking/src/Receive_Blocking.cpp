/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 IRL Receive_Blocking
 Receives IR signals and blocks until the data is read.
 */

#include "IRLremote.h"

// see readme to choose the right pin (with an interrupt!) for your Arduino board
const int pinReceiveIR = digitalPinToInterrupt(2);

void setup() {
  // start serial debug output
  Serial.begin(57600);
  Serial.println("Startup - Receive_Blocking");

  // choose your protocol here to reduce flash/ram/performance
  // see readme for more information
  IRLbegin<IR_ALL>(pinReceiveIR);
}

void loop() {
  // this will get the first valid input, and blocks until you reset below
  if (IRLavailable()) {
    // print as much as you want in this function
    // see source to terminate what number is for each protocol

    Serial.print("Protocol:");
    Serial.print(IRLgetProtocol());
    Serial.print("   Address:0x");
    Serial.print(IRLgetAddress(), HEX);
    Serial.print("   Command:0x");
    Serial.println(IRLgetCommand(), HEX);

    // resume reading to get new values
    IRLreset();
  }
}
