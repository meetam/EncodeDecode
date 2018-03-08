/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * Uncompress.cpp:
 * Reads file produced by compress.cpp. Builds a Huffman coding tree and
 * decodes the input file using BitInputStream.
 */

#include<iostream>
#include<cstdlib>
#include<fstream>
#include "HCTree.h"
#include "BitInputStream.h"

using namespace std;

/**
 * Reads file and outputs to other file.
 * Parameters:
 *   argv[1] - infile
 *   argv[2] - outfile 
 */  
int main(int argc, char ** argv)
{
  //Check for Arguments
  if (argc != 3)
  {
    cout << "Invalid number of arguments.\n" 
         << "Usage: ./uncompress infile outfile\n";
    return -1;
  }

  ifstream in;
  ofstream out;
  std::vector<int> freqs(256, 0); //initialize all freqs to 0

  //Read file header
  in.open(argv[1]);
  //for (int i = 0; i < freqs.size(); i++)
  while (true)
  {
    int symbol;
    int freq;

    //Check for end
    in >> symbol;
    if (symbol == 300)
    {
      break;
    }

    in >> freq;
    freqs[symbol] = freq;
    //freqs[i] = freq;
  }

  in.get(); //Read in new line 

  //Build Huffman tree
  HCTree hct;
  hct.build(freqs);

  //Initialize BitInputStream
  BitInputStream bis(in);

  //Decode and write to out
  out.open(argv[2]);
  while (true)
  { 
    /* Old decode (Commented) */
    //int symbol = hct.decode(in);
    
    /* New decode using BitInputStream */
    int symbol = hct.decode(bis);

    if (in.eof())
    {
      break;
    }

    //Handle case that there are unwritten bits at the end
    if (freqs[symbol] > 0)
    {
      out << (char)symbol; 
    }

    freqs[symbol]--;
  }

  in.close();
  out.close();
  return 0;
}  
