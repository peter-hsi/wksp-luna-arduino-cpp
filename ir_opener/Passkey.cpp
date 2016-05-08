/*
 * Passkey.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: peter
 */

#include "Passkey.h"

Passkey::Passkey(int mk)
{
  masterkey = mk;
  nKS = 0;
}


/*******************/
int Passkey::increment_nKS()
{
  nKS = nKS+1;
  return nKS;
}

int Passkey::get_nKS()
{
  return nKS;
}

void Passkey::reset_nks()
{
  nKS = 0;
}

// TODO - re-write this as an overloaded operator?
bool Passkey::mk_match(int * b)
{
  if ( *b == masterkey)
    return true;
  else
    return false;
}
