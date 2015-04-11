/*
  Run-Length Encoding (decoder)
  a lossless data compression algorithm

  The main function takes as argument
  arg1: input file name, the text that should be encoded.
        This shall be an ASCII-only text file containing 
        only chars 0-9 and the two chars defined in zomap.

  It then writes the following files:
  fout1: output file name: see fname1, the decoded text.
         Contains only chars '0' and '1'.

*/

#include <cstdio>
#define INPUT_BUFFER_SIZE 1000000
#define OUTPUT_BUFFER_SIZE 1000000
const char zomap[] = "XY"; // zero-, one-mapping; 'X'->'0', 'Y'->'1'
const char fname1[] = "RLE_decoded.txt";

// S: input string
// slen: length of S
// C: output string, consisting only of '0' and '1'
// returns number of bytes written to C
int RLE_decoder(char const * const S, const int slen, char * const C) {
  int ci = 0, count;
  char base = '?';
  for (int i = 0; i < slen; i++) {
    if (S[i] == zomap[0] || S[i] == zomap[1]) {
      base = (S[i] == zomap[0]) ? '0' : '1';
      C[ci++] = base;
      count = 0;
      continue;
    }

    while (S[i] >= '0' && S[i] <= '9') {
      count *= 10;
      count += S[i] - '0';
      i++;
    }
    i--;

    for (int j = 0; j < count; j++) {
      C[ci++] = base;
    }
    count = 0;
  }
  return ci;
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

  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);

  // check if input is correctly formatted
  int si = 0;
  while (si++ < slen) {
    if (!((S[si - 1] >= '0' && S[si - 1] <= '9') || S[si - 1] == zomap[0] ||
	  S[si - 1] == zomap[1])) {
      fprintf(stderr, "Input file %s contains char %c (%d) which is not "
	      "included in the provided alphabet.\n", argv[1], S[si - 1],
	      (int) S[si - 1]);
      return 1;
    }
  }

  char* C = new char[OUTPUT_BUFFER_SIZE];  // output
  printf("Run-Length decoding (base 10)...\n");
  int clen = RLE_decoder(S, slen, C);
  // fout1
  fwrite(C, sizeof(char), clen, fout1);
}
