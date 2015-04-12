/* 
   A simple program that takes a file
   and produces a list containing its alphabet (a 
   string in which every distinct char in the 
   file appears exactly once).

   The main function takes as argument
   arg1: input file name, the alphabet of this file
         will be produced.
*/

#include <cstdio>
#include <cstring>
#define INPUT_BUFFER_SIZE 10000000

int main(int argc, char** argv) {
  if (argc != 2) {
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

  // mark which chars appeared
  bool B[256] = { false };
  for (int i = 0; i < slen; i++) 
    B[(unsigned char) S[i]] = true;

  int count = 0;
  for (int i = 0; i < 256; i++) 
    if (B[i])
      count++;
  
  printf("Alphabet size: %d\n\n", count);
  for (int i = 0; i < 256; i++) 
    if (B[i]) 
      printf("%c", (char) i);
  printf("\n");
}
