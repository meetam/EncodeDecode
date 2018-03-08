/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * BitInputStream.h: 
 * Initializes the bit input stream and declares the methods that are in
 * BitInputStream.cpp.
 */

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <fstream>
using namespace std;

/**
 * Initializes the bit input stream and declares the methods that are in 
 * BitInputStream.cpp.
 */ 
class BitInputStream
{
  private:
    unsigned char buf; //Bitwise buffer (one byte)
    int nbits; //Number of bits read from buffer
    istream & in; //Reference to the bytewise input stream

  public:
    /**
     * Constructor: assign 'in' to 'is', 'buf' to 0, and 'nbits' to 8
     */ 
    BitInputStream(istream & is) : in(is), buf(0), nbits(8) {}

    /**
     * Fill buffer by reading one byte from input stream.
     */  
    void fill();

    /**
     * Read bit from bitwise buffer.
     */  
    unsigned int readBit();
};

#endif // BITINPUTSTREAM_H
