/*
  Run-Length Coding (encoder)
  a rather straight-forward lossless data compression algorithm

  The main function takes as argument
  arg1: input file name, this shall be a ASCII-only textfile
        containing only '0' and '1'.

  It then writes the following files:
  fout1: output file name: see fname1,
         specifies the output
  fout2: output file name: see fname2, 
         the alphabet used in Run-Length encoding read from the file specified by arg2	 
*/

#include <cstdio>
#include <iostream>
char O[] = "XY1234567890";
const char fname1[] = "RLE_alphabet.txt";
const char fname2[] = "RLE_encoded.txt";

void RLE(char* S, FILE* fout2) {
  int slen = strlen(S);
  for (int i = 0; i < slen;) {
    int cnt;
    char base;
    for (cnt = 0, base = S[i++] == '0' ? O[0] : O[1]; 
	 S[i] != '\0' && (S[i] - '0' == base - O[0]); i++, cnt++);
    if (cnt == 0) {
      printf("%c", base);
      fprintf(fout2, "%c", base);
    }
    else {
      printf("%c%d", base, cnt);
      fprintf(fout2, "%c%d", base, cnt);
    }
  }
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
  FILE *fout2 = fopen(fname2, "w");

  // read input
  char S[1000000];
  fread(S, sizeof(char), sizeof(S), fin1);
  int si = 0;
  // check if input is correctly formatted
  while (S[si++] != '\0') {
    if ( !(S[si - 1] == '0' || S[si - 1] == '1')) {
      fprintf(stderr, "Input file %s does not contain only 0s and 1s.\n", argv[1]);
      return 1;
    }
  }

  int olen = strlen(O);
  printf("The output alphabet: ");
  for (int i = 0; i < olen; i++) {
    printf("%c", O[i]);
    fprintf(fout2, "%c", O[i]);
    if (i != olen-1) 
      printf(", ");
    else 
      printf("\n");
  }

  printf("Run-Length Encoding...\n");
  RLE(S, fout2);
  fprintf(fout1, "%s", S);
}
