/*
  Fast Lempel-Ziv-Welch (encoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, the file that should be encoded.

  It then writes the following file:
  fout1: output file name: see fname1, the compressed output.

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#define INPUT_BUFFER_SIZE 10000000
#define OUTPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 300
#define SET_NTH_BIT(C, i, n) C[(i)] |= (1 << (n))
const char fname1[] = "LZW_encoded.fastlzw";
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
  int entries = alen, clen = 0;
  memset(C, 0, OUTPUT_BUFFER_SIZE);
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
    for (int j = rbits - 1; j >= 0; j--) {
      if ((found >> j) & 1)
	SET_NTH_BIT(C, clen / 8, clen % 8);
      clen++;
    }
  }
  return clen;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return 1;
  }
  
  FILE *fin1 = fopen(argv[1], "r");
  if (fin1 == NULL) {
    fprintf(stderr, "Input file %s could not be opened.\n", argv[1]);
    return 1;
  }

  FILE *fout1 = fopen(fname1, "w");

  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);

  char A[ALPHABET_BUFFER_SIZE];
  int alen = 0;
  bool Amap[256] = { false };
  for (int i = 0; i < slen; i++)
    Amap[(unsigned char) S[i]] = true;

  for (int i = 0; i < 256; i++) 
    if (Amap[i]) 
      A[1 + alen++] = (char) i; // A[0] stores length
  A[0] = (char) (alen-1);  // -1 needed  here, since
  // 256 would map to 0, but 0 can never occur, add +1
  // on decoder side

  printf("Fast Lempel-Ziv-Welch...\n");
  char* C = new char[OUTPUT_BUFFER_SIZE];
  int clen = LZW_encoder(&A[1], alen, S, slen, C);
  fwrite(A, sizeof(char), alen+1, fout1);
  fwrite(&clen, sizeof(char), sizeof(int), fout1); // output file size < 2 GB
  fwrite(C, sizeof(char), (clen + 7) / 8, fout1);
}
