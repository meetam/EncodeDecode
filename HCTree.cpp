/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * HCTree.cpp:
 * Contains methods to build a Huffman coding tree and encode and decode its
 * symbols.
 */ 

#include "HCTree.h"
#include<queue>
#include<stack>
#include<string>

using namespace std;

/* Destructor */
HCTree::~HCTree()
{
  delete root;
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)
{
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> heap;
  HCNode * n1;
  HCNode * n2;
  HCNode * newNode;

  //Fill leaves
  for (int i = 0; i < freqs.size(); i++)
  {
    if (freqs[i] > 0) //if symbol exists
    {
      newNode = new HCNode(freqs[i], i, 0, 0, 0);
      heap.push(newNode);
      leaves[i] = newNode;
    }
  }

  while (true)
  {
    //Get two smallest nodes
    HCNode * n1 = heap.top();
    heap.pop();
    HCNode * n2 = heap.top();
    heap.pop();

    //Set children and parents
    newNode = new HCNode(n1->count + n2->count, 0, n1, n2, 0);
    n1->p = newNode;
    n2->p = newNode;

    heap.push(newNode);
 
    if (heap.size() == 1)
    {
      root = newNode;
      break;
    }
  }  
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode * curr;
  std::stack<int> code; 
 
  //Find symbol in leaves
  curr = leaves[symbol];

  if (!curr)
  {
    return;
  }

  //Traverse up tree
  while (true)
  {
    if (curr->p) //Current node's parent exists
    {
      //Parent's 0 child is curr
      if (curr->p->c0 && curr->p->c0 == curr)
      {
        code.push(0);
        curr = curr->p;
      }
    
      //Parent's 1 child is curr
      else
      {
        code.push(1);
        curr = curr->p;
      }
    }

    else
    {
      break;
    }
  }

  //Write to BitOutputStream
  while (!code.empty())
  {
    out.writeBit(code.top());
    code.pop();
  }
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
  HCNode * curr;
  std::stack<char> code; 
 
  //Find symbol in leaves
  curr = leaves[symbol];

  if (!curr)
  {
    return;
  }

  //Traverse up tree
  while (true)
  {
    if (curr->p) //Current node's parent exists
    {
      //Parent's 0 child is curr
      if (curr->p->c0 && curr->p->c0 == curr)
      {
        code.push('0');
        curr = curr->p;
      }
    
      //Parent's 1 child is curr
      else
      {
        code.push('1');
        curr = curr->p;
      }
    }

    else
    {
      break;
    }
  }

  //Write to ofstream
  while (!code.empty())
  {
    out << code.top();
    code.pop();
  }
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const
{
  HCNode * curr = root;

  while (curr->c0 || curr->c1)
  {
    unsigned int next = in.readBit();
    if (next == 0)
    {
      curr = curr->c0;
    }

    else if (next == 1)
    {
      curr = curr->c1;
    }
  }

  return curr->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const
{
  HCNode * curr = root;

  while (curr->c0 || curr->c1)
  {
    unsigned char next = (int)in.get();   

    if (next == '0')
    {
      curr = curr->c0; 
    }

    else if (next == '1')
    {
      curr = curr->c1;
    }

    if (in.eof())
    {
      break;
    }
  }

  return curr->symbol;
}

