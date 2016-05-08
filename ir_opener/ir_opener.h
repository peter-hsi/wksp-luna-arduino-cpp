#ifndef _ir_opener_H_
#define _ir_opener_H_

#include <Arduino.h>
#include <IRremote.h>
#include "Door.h"
#include "Passkey.h"
#include "countdownTimer.h"
#include "rc5.h"



int processInput(decode_results *res, Passkey *pk);
void blink(int times);


#endif /* _ir_opener_H_ */
