/*
 * Door.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: peter
 */
#include "Door.h"

#define DB

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
  unsigned long last = millis();
  digitalWrite(relayPin, HIGH);
  while ( millis()-last <  relayWait )
  {}
  digitalWrite(relayPin, LOW);
}

void Door::set_prevOpen(unsigned long p)
{
  prevOpen = p;
}

unsigned long Door::get_prevOpen()
{
    return prevOpen;
}


bool Door::timeExpired(unsigned long now)
{
  #ifdef DB
  Serial.print ("Timeout=");
  Serial.print (reopenTimeout);
  Serial.print ("=  p=");
  Serial.print (prevOpen);
  Serial.print ("=  now=");
  Serial.println (now);
  #endif

  if (now-prevOpen < reopenTimeout)
  {
    prevOpen = now;
    return false;
  }
  else
  {
    prevOpen = now;
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
