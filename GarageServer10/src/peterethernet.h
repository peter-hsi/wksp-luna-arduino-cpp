/*
 * peterethernet.h
 *
 *  Created on: Oct 28, 2014
 *      Author: peter
 */

#ifndef PETERETHERNET_H_
#define PETERETHERNET_H_

#include <Arduino.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <TextFinder.h>
#include "WebServer.h"
#include "Receive_Raw.h"

#include "Relay.h"


const byte mac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const IPAddress ip(10, 1, 1, 100);
char buffer[8]; // make this buffer big enough to hold requested page names

EthernetServer server(80);



#endif /* PETERETHERNET_H_ */
