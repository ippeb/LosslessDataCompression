/*

  Alphabet conversion (encoder)

  The main function takes as argument
  arg1: input file name, this file shall only 
        contain '0' and '1'
  arg2: output file name, this file may contain
        ASCII chars from 0 to 256

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <cstring>
#include <stack>
#define INPUT_BUFFER_SIZE 10000000

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments specified\n");
    return -1;
  }
  
  FILE *fin1 = fopen(argv[1], "r");

  if (fin1 == NULL) {
    fprintf(stderr, "Input file %s could not be opened\n", argv[1]);
    return -1;
  }

  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);

  FILE *fout1 = fopen(argv[2], "w");

  // output
  char* O = new char[INPUT_BUFFER_SIZE];
  for (int i = 0; i < slen; i+=8) {
    O[i/8] = 0;
    for (int j = 0; j < 8; j++) 
      if (S[i+j] == '1')
	O[i/8] |= 1 << j;
  }
  fwrite(O, sizeof(char), (slen + 7)/8,  fout1);
}
