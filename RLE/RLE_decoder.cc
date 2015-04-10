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
#include <iostream>
#define INPUT_BUFFER_SIZE 1000000
#define OUTPUT_BUFFER_SIZE 1000000
const char zomap[] = "XY"; // zero-, one-mapping; 'X'->'0', 'Y'->'1'
const char fname1[] = "RLE_decoded.txt";

// S: input string
// C: output string, consisting only of '0' and '1'
void RLE_decoder(char* S, char *C) {
  int slen = strlen(S), ci = 0, count;
  char base = '?';
  for (int i = 0; i < slen; i++) {
    if (S[i] == zomap[0] || S[i] == zomap[1]) {
      base = (S[i] == zomap[0]) ? '0' : '1';
      C[ci++] = base;
      printf("%c", base);
      count = 0;
      continue;
    }

    while (S[i] >= '0' && S[i] <= '9') {
      count *= 10;
      count += S[i] - '0';
      i++;
    }
    i--;
    printf("(%d)", count);
    for (int j = 0; j < count; j++) {
      C[ci++] = base;
      printf("%c", base);
    }
    printf("\n");
    count = 0;
  }
  C[ci] = '\0';
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
  char S[INPUT_BUFFER_SIZE];
  fread(S, sizeof(char), sizeof(S), fin1);

  // check if input is correctly formatted
  int si = 0;
  while (S[si++] != '\0') {
    if (!((S[si - 1] >= '0' && S[si - 1] <= '9') || S[si - 1] == zomap[0] ||
	  S[si - 1] == zomap[1])) {
      fprintf(stderr, "Input file %s contains char %c (%d) which is not "
	      "included in the provided alphabet.\n", argv[1], S[si - 1],
	      (int) S[si - 1]);
      return 1;
    }
  }

  char C[OUTPUT_BUFFER_SIZE];  // output
  printf("Run-Length decoding (base 10)...\n");
  RLE_decoder(S, C);
  // fout1
  fprintf(fout1, "%s", C);
}
