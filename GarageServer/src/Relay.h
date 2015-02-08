/*
 * Relay.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Peter Hsi
 */

#ifndef RELAY_H_
#define RELAY_H_

// *** pin setting
const int PIN_IRRECV = 11;
const int PIN_RELAY = 8;
const int PIN_LED = 13;
const unsigned int WAITTIME = 1250u;

void mom_on(int p);
void blink(int times);

#endif /* RELAY_H_ */
