/* 

   A simple program that takes a file
   and produces a list containing its alphabet (a 
   string in which every distinct char in the 
   file appears exactly once).

   The main function takes as argument
   arg1: input file name, the alphabet of this file
         will be produced.
   arg2: output file name.

*/

#include <cstdio>
#include <iostream>
#include <cstring>
#define INPUT_LIMIT 1000000


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

  FILE *fout1 = fopen(argv[2], "w");

  // read input
  char S[INPUT_LIMIT];
  fread(S, sizeof(char), sizeof(S), fin1);

  // mark which chars appeared
  int slen = std::strlen(S);
  bool B[256];
  memset(B, 0, sizeof(B));
  for (int i = 0; i < slen; i++) 
    B[S[i]] = true;

  int count = 0;
  for (int i = 0; i < 256; i++) 
    if (B[i]) {
      fprintf(fout1, "%c", (char) i);
      count++;
    }
  
  // debug info
  printf("Alphabet size: %d\n\n", count);
  printf(">>>");
  for (int i = 0; i < 256; i++) 
    if (B[i]) 
      printf("%c", (char) i);
  printf("\n");

}
   
