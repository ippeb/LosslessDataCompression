/*
  Fast Lempel-Ziv-Welch (decoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, the output of the Fast LZW encoder.
 
  It then writes the following files:
  fout1: output file name: see fname1, the output string after 
         decoding. 

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include <map>
#include <utility>

#define INPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 300
const char fname1[] = "LZW_decoded.txt";
using std::vector;
using std::string;

using std::map;
using std::pair;

int num_bits(int x) {
  int bits = 0;
  while (x >>= 1) ++bits;
  return bits+1;
}

void LZW_decoder(char const * const A, const int alen,  char const * const S, 
		 const int slen, string& T) {
  vector<string> MIS;
  MIS.resize(alen + slen);

  int entries = alen;
  for (int i = 0; i < alen; i++) {
    string tempchar(A+i, A+i+1);
    MIS[i] = tempchar;
  }

  string previous;
  int value = 0, i = 0;
  while (i < slen) {
    int rbits = num_bits(entries);
    if (slen - i < rbits) {
      fprintf(stderr, "ERROR, %d bits undecoded.\n", slen - i);
      return;
    }
    
    value = 0;
    for (int j = i; j < i + rbits; j++) {
      value *= 2;
      value += S[j] - '0';
    }

    string curr = "", tmp;
    if (value < entries) {
      curr = MIS[value];
      T += curr;
      tmp = previous + curr[0];
      previous = curr;
      if (i != 0) 
	MIS[entries++] = tmp;
    }
    else {
      curr = previous + previous[0];
      T += curr;
      MIS[entries++] = curr;
      previous = curr;
    }
    i += rbits;    
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return -1;
  }

  FILE *fin1 = fopen(argv[1], "r");
  if (fin1 == NULL) {
    fprintf(stderr, "Input file %s could not be opened.\n", argv[1]);
    return -1;
  }

  FILE *fout1 = fopen(fname1, "w");
  
  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int file_len = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);
  // compute alen, slen
  int alen = (unsigned char) S[0] + 1;
  int slen = file_len - alen - 1;
  // LZW
  printf("Lempel-Ziv-Welch decoding...\n");
  string T;
  LZW_decoder(&S[1], alen, &S[alen + 1], slen, T);
  // fout1
  fwrite(T.c_str(), sizeof(char), T.length(), fout1);
}
