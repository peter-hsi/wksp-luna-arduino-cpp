/*
 * ir_opener15.cpp
 *
 *  Created on: Sept 1, 2014
 *      Author: peter
 *
 * API:
 *  Arduino ver. 1.6.x
 *  IRLremote ver 2.x
 *
 *  TODO
 *  x add timeout period to open a closed door without having to re-enter the masterkey
 *  x get rid of hardcoded values!!!
 *  - user modifiable keys
 *  - better way of comparing keys (hash function?)
 *  - store keys in EEPROM
 */

#include "ir_opener.h"

#define DB  debug

//const int PIN_IRRECV    = 11;
//const int PIN_RELAY     = 3;
//const int PIN_LED       = 13;
//const int PIN_DOOROPEN  = 5;
//const int MASTERKEY     = 9028;
//const unsigned long TIMEOUT  = 10000ul;     // 10 seconds

#define PIN_IRRECV    11
#define PIN_RELAY     3
#define PIN_LED       13
#define PIN_DOOROPEN  5
#define MASTERKEY     9028
#define TIMEOUT       10000ul

countdownTimer cd(TIMEOUT);

IRrecv         irrecv( PIN_IRRECV);
decode_results results;
Door           gdoor( PIN_DOOROPEN, PIN_IRRECV, PIN_RELAY, 1250ul);
Passkey        pkey( MASTERKEY);

int            inputBuff = 0;  // TODO need a better way of handling input buffer!!!

void setup()
{
  Serial.begin(57600, SERIAL_8N1); //Serial.begin(9600, SERIAL_8N1);
  Serial.println("setup...");

  pinMode(PIN_RELAY,    OUTPUT);
  pinMode(PIN_LED,      OUTPUT);
  pinMode(PIN_DOOROPEN, INPUT_PULLUP);

  irrecv.enableIRIn();
}


void loop()
{
  if (irrecv.decode(&results) )    // keypress detected, stored at "results"
  {
    if ( cd.expired(millis()) && !gdoor.isOpen() )   // if expired and door not opened, user is required to enter passcode
    {
      if ( processInput(&results, &pkey)==0 )    // if passcode correct, open door
      {
        cd.set_prevOpen(millis());
        #ifdef DB
        Serial.println ("=1 MomOn");
        #else
        gdoor.momentaryOn();
        #endif
      }
    }
    else  // door open: close/reverse door
    {
      #ifdef DB
      Serial.println ("=2 DOOR OPEN and KEYSTROKE DETECTED");
      Serial.println ("=2 MomOn)");
      #else
      gdoor.momentaryOn();
      #endif
    }

    blink(1);
    irrecv.resume();  // resume receiving key presses
  }
}



int processInput(decode_results *res, Passkey *pk)
{
  if ( lowByte(res->value)==STBY  ) //if ( res->value == STBY || res->value == 0x80c )
  {
    if ( pk->mk_match(&inputBuff) ) // check if input matches masterkey
    {
      Serial.println("Open sesame!");
      inputBuff = 0;
      pk->reset_nks();
      return 0; // Success!
    }
    else
    {
      Serial.println("=1 On/off pressed, resetting");
      inputBuff = 0;
      pk->reset_nks();
      return 1; // reset
    }
  }
  else if (pk->increment_nKS() > 4 )
  {
    Serial.println("=2 Buffer full, resetting");
    inputBuff = 0;
    pk->reset_nks();
    return 2; // reset
  }
  else
  {
    // passcode
    // TODO find another way to buffer keystrokes
    int digit = (unsigned int) lowByte(res->value);     // get the low bytes

    #ifdef DB
    Serial.print("=0x");
    Serial.print(res->value, HEX);
    Serial.print(", digit=");
    Serial.print(digit);
    Serial.print(", nStrokes=");
    Serial.print(pk->get_nKS());
    #endif

    int pow10 = 1;
    for (int i=0; i<(4-pk->get_nKS()); i=i+1)
      pow10 = 10 * pow10;
    inputBuff = (digit * pow10) + inputBuff;

    #ifdef DB
    Serial.print(", inputBuff=");
    Serial.println(inputBuff);
    #endif
  }
  return 3;
}






void blink(int times = 0)
{
  do
  {
    digitalWrite(PIN_LED, HIGH);
    delay(100);
    digitalWrite(PIN_LED, LOW);
    delay(100);
    times = times - 1;
  } while (times > 0);
}
