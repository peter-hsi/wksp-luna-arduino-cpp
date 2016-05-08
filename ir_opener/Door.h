/*
 * Door.h
 *
 *  Created on: Oct 13, 2014
 *      Author: peter
 */

#ifndef DOOR_H_
#define DOOR_H_

#include <Arduino.h>

class Door
{
  public:
    Door(int p1, int p2, int p3, unsigned long t);

    bool isOpen();
    void momentaryOn();

  private:
    int           openSensePin;   //digital pin
    int           irRecvPin;      //analog pin
    int           relayPin;       //digital pin
    unsigned long relayMomMs;     // relay momentary-on, milliseconds
};

#endif /* DOOR_H_ */
