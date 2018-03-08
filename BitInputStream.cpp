/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * BitInputStream.cpp:
 * Contains methods to read bits from an in file.
 */

#include "BitInputStream.h"

using namespace std;

/**
 * Fill buffer by reading one byte from input stream.
 */  
void BitInputStream::fill()
{
  buf = in.get(); //Read a byte
  nbits = 0;
}

/**
 * Read bit from bitwise buffer.
 */  
unsigned int BitInputStream::readBit()
{
  //Fill buffer if no more unread bits
  if (nbits == 8)
  {
    fill();
  }

  //Get next unread bit from buffer
  unsigned int nextBit = (buf >> (7 - nbits)) & 1; 

  nbits++;
  return nextBit;
}
