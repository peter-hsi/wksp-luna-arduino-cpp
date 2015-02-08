/*
 * Relay.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: Peter Hsi
 */

#include <Arduino.h>
#include "Relay.h"

//set HIGH, wait x millisec, and set LOW
void mom_on(int pin = 8)
{
  unsigned long last = millis();
  digitalWrite(pin, HIGH);
  while (millis() - last < WAITTIME)
  {
  }
  digitalWrite(pin, LOW);
}

void blink(int times = 0)
{
  do
  {
    digitalWrite(PIN_LED, HIGH);
    delay(300);
    digitalWrite(PIN_LED, LOW);
    delay(100);
    times = times - 1;
  } while (times > 0);
}
