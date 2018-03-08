/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * HCNode.cpp: 
 * Contains node comparison method for the min heap. Defines the destructor.
 */ 

#include "HCNode.h"

typedef unsigned char byte;
using namespace std;

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode &other)
{
  //Gives priority to smaller count
  if (count != other.count)
  {
    return (count > other.count);
  }

  //Gives priority to smaller symbol
  return (symbol > other.symbol);    
}

/* Destructor */
HCNode::~HCNode()
{
  //Recursively call delete on children
  delete c0;
  delete c1;
}
