/*
 * Door.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: peter
 */
#include <Arduino.h>
#include "Door.h"


Door::Door(int p1, int p2, int p3, long x)
{
  openSensePin  = p1;
  irRecvPin     = p2;
  relayPin      = p3;
  relayWait     = 1250;
  reopenTimeout = x;
  prevOpen      = millis();
  isLock        = true;
}


Door::~Door()
{}


/*
 * Door sensor is normally open (NO) when door is open.
 */
bool Door::isOpen()
{
  if ( digitalRead(openSensePin) == HIGH )
  {
    return true;
  }
  else
    return false;
}


void Door::momentaryOn()
{
  long last = millis();
  digitalWrite(relayPin, HIGH);
  while ( millis()-last <  relayWait )
  {}
  digitalWrite(relayPin, LOW);
}

void Door::set_prevOpen(long p)
{
  prevOpen = p;
}

long Door::get_prevOpen()
{
    return prevOpen;
}


bool Door::timeExpired()
{
  long c = millis();

  #ifdef DB
  Serial.print ("Timeout=");
  Serial.print (reopenTimeout);
  Serial.print ("=  p=");
  Serial.print (prevOpen);
  Serial.print ("=  c=");
  Serial.print (c);
  #endif

  if (c-prevOpen < reopenTimeout)
  {
    Serial.println ("=  not expired");
    prevOpen = c;
    return false;
  }
  else
  {
    Serial.println ("=  expired");
    prevOpen = c;
    return true;  // expired
  }
}

void Door::set_isLock(bool b)
{
  isLock=b;
}

bool Door::get_isLock()
{
  return isLock;
}
