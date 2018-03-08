/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * BitOutputStream.h:
 * Intializes the bit output stream and declares the methods that are in
 * BitOutputStream.cpp.
 */

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <fstream>
using namespace std;

/**
 * Initializes the bit output stream and declares the methods that are in
 * BitOutputStream.cpp.
 */ 
class BitOutputStream
{  
  private:
    unsigned char buf; //Bitwise buffer (one byte)
    int nbits; //Number of bits written to the bitwise buffer
    ostream & out; //Reference to bytewise output stream

  public:
    /**
     * Constructor: assign 'out' to 'os', 'buf' to 0, and 'nbits' to 0
     */
    BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}

    /**
     * Send the bitwise buffer to the output stream. Clear the bitwise buffer.
     */ 
    void flush();

    /**
     * Write bit to bitwise buffer.
     */
    void writeBit(unsigned int bit);             
};

#endif // BITOUTPUTSTREAM_H
