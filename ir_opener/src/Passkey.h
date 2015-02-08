/*
 * Passkey.h
 *
 *  Created on: Oct 13, 2014
 *      Author: peter
 */

#ifndef PASSKEY_H_
#define PASSKEY_H_

class Passkey
{
  public:
    Passkey(int masterkey);
    virtual ~Passkey();


    int increment_nKS();
    int get_nKS();

    void reset_nks();

    bool mk_match(int * buff);

  private:
    int masterkey;
    int nKS;

};

#endif /* PASSKEY_H_ */
