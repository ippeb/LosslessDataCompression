/*
  Lempel-Ziv-Welch (encoder)
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
  fout3: file name: see fname3, C code declaring the 
         alphabet (the content of fout2).

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <utility>
#define INPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 1000
const char fname1[] = "LZW_encoded.txt";
const char fname2[] = "LZW_alphabet.txt";
const char fname3[] = "LZW_alphabet_C.txt";
using std::map;
using std::vector;
using std::string;
using std::stack;
using std::pair;
using std::make_pair;

// return the number of bits integer x contains
int num_bits(int x) {
  if (x == 0) // special case 
    return 1;
  int bits = 0;
  while (x > 0) {
    x /= 2;
    bits++;
  }
  return bits;
}

// A = {a_1, ..., a_alen} alphabet, as an array of chars
//   it is assumed that 0 <= a_i <= n-1 and all a_i are
//   distinct, A is terminated with a '0' (C string)
// S = {s_1, ..., s_slen} input char string, null terminated
// C = {c_1, ..., c_m} output binary sequence
void LZW_encoder(char const * const A, const int alen, char const * const S, 
		 const int slen,  vector<bool>& C) {
  // M = (u_i, v_i) LZW extended dictionary, map string u_i to code number v_i
  map<string, int> MSI;
  map<int, string> MIS; // reverse mapping
  MSI.clear();
  MIS.clear();
  // initialize the dictionary to contain all strings of  length one
  int entries = alen;
  for (int i = 0; i < alen; i++) {
    string tempchar(A+i, A+i+1);
    MIS[i] = tempchar;
    MSI[tempchar] = i;
  }

  C.clear();
  for (int i = 0; i < slen; i++) {
    // find longest string W in the dictionary that matches the current input
    string curr(S+i, S+i+1);
    int found = -1;
    while (MSI.find(curr) != MSI.end() && i < slen) {
      found = MSI[curr];
      curr += S[++i];
    }
    i--;
    if (found != -1) 
      printf("found:     %7d (%s) ", found, MIS[found].c_str());
    else {
      // ERROR
      fprintf(stderr, "LZW_encoder error at %d, alen %d slen %d\n", i, alen, slen);
      return;
    }

    if (i != slen-1) {
      MSI[curr] = entries;
      MIS[entries] = curr;
    }
    // transform "found" to binary and save to output
    // this binary number needs to have log_2(entries) (rounded 
    // down) digits
    printf("[");
    int rbits = num_bits(i == 0 ? entries : entries-1);
    for (int j = rbits - 1; j >= 0; j--) {
      C.push_back((found >> j)&1);
      printf("%d", (found >> j)&1);
    }
    printf("]\n");
    
    // debug
    if (i+1 != slen) {
      printf("new entry: %7d (%s)\n", entries, curr.c_str());
      entries++;
    }
  }

  printf("\nDictionary\n");
  for (map<int, string>::iterator it  = MIS.begin(); it != MIS.end(); it++) {
    printf("%3d: %s\n", it->first, it->second.c_str());
  }
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
  FILE *fout3 = fopen(fname3, "w");

  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);
  // read alphabet 
  char A[ALPHABET_BUFFER_SIZE];
  int alen;
  if (argc >= 3) {
    alen = fread(A, sizeof(char), ALPHABET_BUFFER_SIZE, fin2);
  }
  else {
    // generate alphabet
    alen = 0;
    bool Amap[256] = { false };
    for (int i = 0; i < slen; i++)
      Amap[(unsigned char) S[i]] = true;
    for (int i = 0; i < 256; i++) 
      if (Amap[i]) 
	A[alen++] = (char) i;
  }

  printf("The alphabet: ");
  for (int i = 0; i < alen; i++) {
    printf("%c", A[i]);
    if (i != alen-1) 
      printf(", ");
    else 
      printf("\n");
  }

  printf("Lempel-Ziv-Welch...\n");
  vector<bool> C;
  LZW_encoder(A, alen, S, slen, C);
    
  // print output
  for (vector<bool>::iterator it = C.begin(); it != C.end(); it++) {
    printf("%c", '0' + *it );
  }
  printf("\n");

  // fout1
  for (vector<bool>::iterator it = C.begin(); it != C.end(); it++) {
    fprintf(fout1, "%c", '0' + *it );
  }

  // fout2
  fwrite(A, sizeof(char), alen, fout2);

  // fout3
  fprintf(fout3, "char A[]=\"");
  for (int i = 0; i < alen; i++) {
    fprintf(fout3, "%c", A[i]);
  }
  fprintf(fout3, "\";\n");
}
