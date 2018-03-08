/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * BitOutputStream.cpp:
 * Contains methods to write bits to an out file.
 */

#include "BitOutputStream.h"

using namespace std;

/**
 * Send the bitwise buffer to the output stream. Clear the bitwise buffer.
 */ 
void BitOutputStream::flush()
{
  out.put(buf); //Write buffer to ostream
  out.flush();

  buf = 0;     
  nbits = 0; 
}

/**
 * Write bit to bitwise buffer.
 */
void BitOutputStream::writeBit(unsigned int bit)
{
  //Flush buffer if full
  if(nbits == 8) 
  {
    flush();
  }

  //Set the next open bit of the bitwise buffer to 'bit'
  buf |= (bit & 1) << (7 - nbits);
            
  nbits++;
}
