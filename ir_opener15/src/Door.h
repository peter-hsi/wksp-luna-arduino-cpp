/*
 * Door.h
 *
 *  Created on: Oct 13, 2014
 *      Author: peter
 */

#ifndef DOOR_H_
#define DOOR_H_

class Door
{
  public:
    Door(int p1, int p2, int p3, long reopen);
    virtual ~Door();

    bool isOpen();
    void momentaryOn();
    void set_prevOpen(long p);
    long get_prevOpen();
    bool timeExpired();
    void set_isLock(bool b);
    bool get_isLock();

  private:
    int openSensePin;
    int irRecvPin;
    int relayPin;
    long relayWait;
    long reopenTimeout;
    long prevOpen;
    bool isLock;
};

#endif /* DOOR_H_ */
