/*
  Fast Lempel-Ziv-Welch (encoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, the text that should be encoded.
        This shall be an ASCII-only text file containing 
        only chars provided by arg2.
  arg2: [optional] file name, the file should only contain 
        an ASCII string specifying the alphabet. 
        If arg2 is not provided, the alphabet is the set
        of characters appearing in the input file (in 
        alphabetical order).

  It then writes the following files:
  fout1: output file name: see fname1, the encoded text.
	 The encoded text only contains '0' and '1'.
  fout2: file name: see fname2, the alphabet read from the 
         file specified by arg2 (if provided).

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#define INPUT_BUFFER_SIZE 10000000
#define OUTPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 1000
const char fname1[] = "LZW_encoded.fastlzw";
const char fname2[] = "LZW_alphabet.txt";
using std::map;
using std::string;

int num_bits(int x) {
  int bits = 0;
  while (x >>= 1) ++bits;
  return bits+1;
}

int LZW_encoder(char const * const A, const int alen, char const * const S, 
		 const int slen,  char * const C) {
  map<string, int> MSI;
  int entries = alen, clen_bit = 0;
  for (int i = 0; i < alen; i++) {
    string tempchar(A+i, A+i+1);
    MSI[tempchar] = i;
  }

  for (int i = 0; i < slen; i++, entries++) {
    string curr(S+i, S+i+1);
    int found = -1;
    while (MSI.find(curr) != MSI.end() && i < slen) {
      found = MSI[curr];
      curr += S[++i];
    }
    i--;
    MSI[curr] = entries;
    int rbits = num_bits(i == 0 ? entries : entries-1);
    for (int j = rbits - 1; j >= 0; j--) 
      C[clen_bit++] = (found >> j) & 1 ? '1' : '0';
  }
  return clen_bit;
}

int main(int argc, char** argv) {
  if (argc > 3 || argc <= 1) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return 1;
  }
  
  FILE *fin1 = fopen(argv[1], "r");
  if (fin1 == NULL) {
    fprintf(stderr, "Input file %s could not be opened.\n", argv[1]);
    return 1;
  }

  FILE *fin2 = fopen(argv[2], "r");
  if (argc >= 3) {
    if (fin2 == NULL) {
      fprintf(stderr, "Input file %s could not be opened.\n", argv[2]);
      return 1;
    }
  }

  FILE *fout1 = fopen(fname1, "w");
  FILE *fout2 = fopen(fname2, "w");

  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);
  char A[ALPHABET_BUFFER_SIZE];
  int alen;
  if (argc >= 3) {
    alen = fread(A, sizeof(char), ALPHABET_BUFFER_SIZE, fin2);
  }
  else {
    alen = 0;
    bool Amap[256] = { false };
    for (int i = 0; i < slen; i++)
      Amap[(unsigned char) S[i]] = true;
    for (int i = 0; i < 256; i++) 
      if (Amap[i]) 
	A[alen++] = (char) i;
  }

  printf("Fast Lempel-Ziv-Welch...\n");
  char* C = new char[OUTPUT_BUFFER_SIZE];
  int clen = LZW_encoder(A, alen, S, slen, C);
  fwrite(C, sizeof(char), clen, fout1);
  fwrite(A, sizeof(char), alen, fout2);
}
