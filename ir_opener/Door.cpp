/*
 * Door.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: peter
 */
#include "Door.h"

#define DB dbg

Door::Door(int p1, int p2, int p3, unsigned long t)
{
  openSensePin = p1;
  irRecvPin = p2;
  relayPin = p3;
  relayMomMs = t;
}
/* ------------------------------------------------------------------------- */
/*
 * Circuit is NO (normally open) when door is open.
 */
bool Door::isOpen()
{
  if (digitalRead( openSensePin ) == HIGH)
    return true;
  else
    return false;
}

/*
 * Set relay pin HIGH for relayMomMs milliseconds
 */
void Door::momentaryOn()
{
  unsigned long last = millis();
  digitalWrite( relayPin, HIGH );
  while (millis() - last < relayMomMs)
  {}
  digitalWrite( relayPin, LOW );
}

