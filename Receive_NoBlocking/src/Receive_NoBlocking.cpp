/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 IRL Receive_NoBlocking
 Receives IR signals and instantly calls an attached interrupt function.
 This may fire more than one time if you press a button too long, add a debounce.
 Dont use Serial inside the interrupt!
 */

#include "IRLremote.h"

// see readme to choose the right pin (with an interrupt!) for your Arduino board
const int interruptIR = digitalPinToInterrupt(2);

// temporary variables to save latest IR input
uint8_t IRProtocol = 0;
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

void setup() {
  // start serial debug output
  Serial.begin(57600);	// 115200
  Serial.println("Startup - Receive_NoBlocking");

  // choose your protocol here to reduce flash/ram/performance
  // see readme for more information
  IRLbegin<IR_NEC>(interruptIR);
}

void loop() {
  // temporary disable interrupts and print newest input
  uint8_t oldSREG = SREG;
  cli();
  if (IRProtocol) {
    // print as much as you want in this function
    // see source to terminate what number is for each protocol

    Serial.print("Protocol:");
    Serial.print(IRProtocol);
    Serial.print("   Address:0x");
    Serial.print(IRAddress, HEX);
    Serial.print("  Command:0x");
    Serial.println(IRCommand, HEX);
	
    // reset variable to not read the same value twice
    IRProtocol = 0;
  }
  SREG = oldSREG;
}

void IREvent(uint8_t protocol, uint16_t address, uint32_t command) {
  // called when directly received an interrupt CHANGE.
  // do not use Serial inside, it can crash your program!

  // update the values to the newest valid input
  IRProtocol = protocol;
  IRAddress = address;
  IRCommand = command;
}
