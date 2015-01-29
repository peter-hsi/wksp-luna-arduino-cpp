/*
 * readTemp.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: peter
 *
 * from https://code.google.com/p/tinkerit/wiki/SecretThermometer
 */

#include <Arduino.h>

long readTemp();


long readTemp()
{
  long result;

  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(2); // Wait for Vref to settle

  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = (result - 125) * 1075;
  return result;
}

