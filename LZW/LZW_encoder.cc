/*
  Lempel-Ziv-Welch (encoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, this shall be an ASCII-only text file.
  arg2: [optional] file name of the input alphabet.

  It then writes the following files:
  fout1: output file name: see fname1,
         specifies the output, after applying LZW. It 
	 only contains '0' and '1'.
  fout2: output file name: see fname2, 
         the alphabet read from the file specified by arg2
         (if provided).
  fout3: output file name: see fname3,
         C code for a 2D C string specifying the alphabet.

*/

#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <utility>
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
// S = {s_1, ..., s_n} input char string, null terminated
// C = {c_1, ..., c_m} output binary sequence
void LZW_encoder(char* A, char* S, vector<bool>& C) {
  int alen = strlen(A), slen = strlen(S);
  int entries = alen;
  // M = (u_i, v_i) LZW extended dictionary, map string u_i
  //     to code number v_i
  map<string, int> MSI;
  map<int, string> MIS; // reverse mapping
  MSI.clear();
  MIS.clear();
  // initialize the dictionary to contain all strings of 
  // length one
  for (int i = 0; i < alen; i++) {
    string tempchar(A+i, A+i+1);
    MIS.insert(make_pair(i, tempchar));
    MSI.insert(make_pair(tempchar, i));
  }
  
  C.clear();
  for (int i = 0; i < slen; i++) {
    // find the longest string W in the dictionary that 
    // matches the current input
    string curr(S+i, S+i+1);
    int found = -1;
    while (MSI.find(curr) != MSI.end() && S[i] != '\0') {
      found = MSI[curr];
      curr += S[++i];
    }
    i--;
    printf("found: %d (%s) ", found, MIS[found].c_str());
    if (S[i+1] != 0) {
      MSI[curr] = entries;
      MIS[entries] = curr;
    }
    // transform "found" to binary and save to output
    // this binary number needs to have log_2(entries) (rounded 
    // down) digits
    if (found != -1) {
      printf("[");
      for (int j = num_bits(entries-1) - 1; j >= 0; j--) {
	C.push_back((found >> j)&1);
	printf("%d", (found >> j)&1);
      }
      printf("]\n");

      // debug
      if (S[i+1] != 0) {
	printf("new entry %d: %s\n", entries, curr.c_str());
	entries++;
      }

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
  char S[1000000];
  fread(S, sizeof(char), sizeof(S), fin1);

  // read alphabet 
  char A[100000];
  int alen;
  if (argc >= 3) {
    fread(A, sizeof(char), sizeof(A), fin2);
    alen = strlen(A);
  }
  else {
    // generate alphabet
    alen = 0;
    bool B[256];
    memset(B, 0, sizeof(B));
    int slen = strlen(S);
    for (int i = 0; i < slen; i++) 
      B[(int) S[i]] = true;

    for (int i = 0; i < 256; i++) 
      if (B[i]) 
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
  LZW_encoder(A, S, C);
  
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
  fprintf(fout2, "%s", A);

  // fout3
  fprintf(fout3, "char A[]=\"");
  for (int i = 0; i < alen; i++) {
    fprintf(fout3, "%c", A[i]);
  }
  fprintf(fout3, "\";\n");
}
