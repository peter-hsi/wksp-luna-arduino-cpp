/*
 * ir_opener15.cpp
 *
 *  Created on: Sept 1, 2014
 *      Author: peter
 *
 * API:
 *  Arduino 1.0.x
 *  IRLremote
 *
 *  TODO
 *  - add timeout period to open a closed door without having to re-enter the masterkey
 *  - get rid of hardcoded values!!!
 *  - user modifiable keys
 *  - better way of comparing keys (hash function?)
 *  - store keys in EEPROM
 */
#include <Arduino.h>
#include <IRremote.h>
#include "Door.h"
#include "Passkey.h"

/*
 *  IO pins
 */
//const int PIN_IRRECV    = 11;
//const int PIN_RELAY     = 3;
//const int PIN_LED       = 13;
//const int PIN_DOOROPEN  = 5;
//const int WAITTIME      = 1250;  // millisecs
//const int MASTERKEY     = 9028;

#define PIN_IRRECV    11
#define PIN_RELAY     3
#define PIN_LED       13
#define PIN_DOOROPEN  5
#define WAITTIME      1250
#define MASTERKEY     9028

const long REOPEN_TIMEOUT  = 10000l; // millisecs

IRrecv          irrecv(PIN_IRRECV);
decode_results  results;
Door            door(PIN_DOOROPEN, PIN_IRRECV, PIN_RELAY, REOPEN_TIMEOUT);
Passkey         pkey(MASTERKEY);


/*
 * input keybuffer
 * TODO find a better way of doing this
 */
int inputBuff = 0;  // input buffer


/*
 * Prototypes
 */
int processInput(decode_results *res, Passkey *pk);
void blink(int times);




void setup()
{
  pinMode(PIN_RELAY,    OUTPUT);
  pinMode(PIN_LED,      OUTPUT);
  pinMode(PIN_DOOROPEN, INPUT_PULLUP);
  irrecv.enableIRIn();

  Serial.begin(9600, SERIAL_8N1); // default: 8 bits, 0 parity, 1 stop
  Serial.println("setup...");
}


void loop()
{
  if (irrecv.decode(&results) )
  {
    //Serial.print (door.timeExpired());

    if ( !door.isOpen() ) // && !door.timeExpired() ) //if ( !door.isOpen())   // door is closed, get passcode
    {
      if (processInput(&results, &pkey)==0 )
      {
        #ifdef DB
        Serial.println ("Mom_on 0");
        #else
        door.momentaryOn();
        #endif
      }
    }
    else if ( door.isOpen() ) //&& !door.timeExpired())   // door is open, close or reverse door
    {
      #ifdef DB
      Serial.println ("=DOOR NOT CLOSED and KEYSTROKE DETECTED");
      Serial.println ("Mom_on 1)");
      #else
      door.momentaryOn();
      #endif
    }

    blink(1);
    irrecv.resume();  // Receive the next value
  }
}



int processInput(decode_results *res, Passkey *pk)
{
  if ( res->value == 0x0c || res->value == 0x80c )
  {
    if ( pk->mk_match(&inputBuff) ) // check if input matches masterkey
    {
      Serial.println("Open sesame!");
      inputBuff = 0;
      pk->reset_nks();
      return 0;
    }
    else
    {
      Serial.println("=1 On/off pressed, resetting");
      inputBuff = 0;
      pk->reset_nks();
      return 1;
    }
  }
  else if (pk->increment_nKS() > 4 )
  {
    Serial.println("=2 Buffer full, resetting");
    inputBuff = 0;
    pk->reset_nks();
    return 2;
  }
  else
  {
    // Assemble passcode
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


/* WORKS
 *
void loop()
{
  if (irrecv.decode(&results) )
  {
    if ( !door.isOpen())   // door is closed, get passcode
    {
      processInput(&results, &pkey);
    }
    else if ( door.isOpen())   // door is open, close or reverse door
    {
      Serial.println ("=DOOR NOT CLOSED and KEYSTROKE DETECTED");
      door.momentaryOn();
    }
    blink(1);
    irrecv.resume();  // Receive the next value
  }
}



int processInput(decode_results *res, Passkey *pk)
{

  if ( pk->increment_nKS() > 4 || res->value == 0x0c || res->value == 0x80c ) // if ( pk->get_nKS() > 4 || res->value == 0x0c || res->value == 0x80c )
  {
    if ( pk->mk_match(&inputBuff) ) // check if input matches masterkey
    {
      Serial.println("OPEN SESAME!");
      door.momentaryOn();
    }
    else
    {
      Serial.println("= On/Off pressed or mkey buffer is full");
    }

    // reinitialize input buffer
    inputBuff = 0;
    pk->reset_nks();
  }
  else
  {
    // Assemble passcode
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
  return 0;
}

 */
