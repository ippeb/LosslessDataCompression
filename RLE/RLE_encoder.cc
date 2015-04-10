/*
  Run-Length Encoding (encoder)
  a rather straight-forward lossless data compression algorithm

  The main function takes as argument
  arg1: input file name, this shall be an ASCII-only text file
        containing only '0' and '1'.

  It then writes the following files:
  fout1: output file name: see fname1, the encoded text.

*/

#include <cstdio>
#include <iostream>
#define INPUT_BUFFER_SIZE 1000000
#define OUTPUT_BUFFER_SIZE 1000000
const char zomap[] = "XY"; // zero-, one-mapping; 'X'->'0', 'Y'->'1'
const char fname1[] = "RLE_encoded.txt";

// S: input string, consisting only of '0' and '1'
// C: output string, consisting only of chars provided by O
void RLE_encoder(char* S, char *C) {
  int slen = strlen(S), ci = 0;
  for (int i = 0; i < slen;) {
    int cnt;  // counts cnt+1 consecutive appearences
    char base;
    for (cnt = 0, base = S[i++] == '0' ?  zomap[0] : zomap[1]; 
	 S[i] != '\0' && (S[i] - '0' == base - zomap[0]); i++, cnt++);
    printf("%c", base);
    C[ci++] = base;
    if (cnt > 0) {
      printf("%d", cnt);
      ci += sprintf(&C[ci], "%d", cnt);
    }
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
  int si = 0;
  // check if input is correctly formatted
  while (S[si++] != '\0') {
    if ( !(S[si - 1] == '0' || S[si - 1] == '1')) {
      fprintf(stderr, "Input file %s does not contain only 0s and 1s.\n", 
	      argv[1]);
      return 1;
    }
  }

  char C[OUTPUT_BUFFER_SIZE];  // output
  printf("Run-Length encoding (base 10)...\n");
  RLE_encoder(S, C);
  // fout1 
  fprintf(fout1, "%s", C);
}
