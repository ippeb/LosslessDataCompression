/*
  Fast Lempel-Ziv-Welch (decoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, this shall be an ASCII text file
        containing only '0' and '1'.
  arg2: input file name, the file should only contain an ASCII
        string specifying the alphabet.
 
  It then writes the following files:
  fout1: output file name: see fname1, the output string after 
         decoding. The symbols (chars) used are specified by
         arg2.

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#define INPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 1000
const char fname1[] = "LZW_decoded.txt";
using std::vector;
using std::string;

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
  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return -1;
  }
  FILE *fin1 = fopen(argv[1], "r");
  FILE *fin2 = fopen(argv[2], "r");

  if (fin1 == NULL || fin2 == NULL) {
    fprintf(stderr, "Input file %s or %s could not be opened.\n", 
	    argv[1], argv[2]);
    return -1;
  }

  FILE *fout1 = fopen(fname1, "w");

  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);

  // read alphabet
  char* A = new char[ALPHABET_BUFFER_SIZE];
  int alen = fread(A, sizeof(char), ALPHABET_BUFFER_SIZE, fin2);

  printf("Lempel-Ziv-Welch decoding...\n");
  string T;
  LZW_decoder(A, alen, S, slen, T);
  // fout1
  fwrite(T.c_str(), sizeof(char), T.length(), fout1);
}
