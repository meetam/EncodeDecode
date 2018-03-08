/**
 * Name: Meeta Marathe
 * Date: November 10, 2017
 * Assignment: PA3
 *
 * Compress.cpp:
 * Reads a file that has a sequence of symbols. Builds an output file that has
 * information to build a Huffman coding tree and encodes the symbols in
 * the input file using BitOutputStream.
 */

#include<iostream>
#include<cstdlib>
#include<fstream>
#include "HCTree.h"
#include "BitOutputStream.h"

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
         << "Usage: ./compress infile outfile\n";
    return -1;
  }

  ifstream in;
  std::vector<int> freqs(256, 0); //initialize all freqs to 0

  //Read infile
  in.open(argv[1]);
  while (true)
  {
    int symbol = (int)in.get();
    if (in.eof())
    {
      break;
    }

    freqs[symbol]++; //Fill freqs
  }
  in.close();

  //Build Huffman tree
  HCTree hct;
  hct.build(freqs);

  ofstream out;
  out.open(argv[2]);

  //Initialize BitOutputStream
  BitOutputStream bos(out);

  //Write file header
  for (int i = 0; i < freqs.size(); i++)
  {
    if (freqs[i] > 0)
    {
      out << i << " " << freqs[i] << endl;
    }

    //out << freqs[i] << endl; 
  }

  out << 300 << endl; //Indicate end

  //Read infile again, encoding each symbol
  in.open(argv[1]);
  while (true)
  {
    unsigned char next = (int)in.get();

    /* Old encode (Commented) */
    //hct.encode(next, out);

    /* New encode using BitOutputStream */
    hct.encode(next, bos);
    
    if (in.eof())
    {
      break;
    } 
  }

  bos.flush();
  in.close();
  out.close();

  return 0;
}
