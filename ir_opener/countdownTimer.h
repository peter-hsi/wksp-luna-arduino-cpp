/*
 * countdownTimer.h
 *
 *  Created on: Mar 4, 2016
 *      Author: peter
 */

#ifndef COUNTDOWNTIMER_H_
#define COUNTDOWNTIMER_H_

class countdownTimer
{
  public:
    countdownTimer(unsigned long x);

    void set_prevOpen(unsigned long p);
    bool expired(unsigned long ms);

  private:
    unsigned long reopenCountdown;
    unsigned long prevOpenMs;
};

#endif /* COUNTDOWNTIMER_H_ */
