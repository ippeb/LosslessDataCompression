/*
  Lempel-Ziv-Welch (decoder)
  lossless data compression algorithm, dictionary coder

  The main function takes as argument
  arg1: input file name, this shall be an ASCII text file
        containing only '0' and '1'.
  arg2: input file name, the file should only contain an ASCII
        string specifying the alphabet.
 
  It then writes the following files:
  fout1: output file name: see fname1, the output string after 
         decoding. The symbols (chars) used are specified by
         arg2.

  Author: Josef Ziegler (ippeb24@gmail.com)

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
const char fname1[] = "LZW_decoded.txt";
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
// S input char string, containing only '0' and '1'
//   (null-terminated)
// T decoded output string (null-terminated)
void LZW_decoder(char const * const A, const int alen,  char const * const S, 
		 const int slen, string& T) {
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

  string previous;
  int value = 0, i = 0;
  while (i < slen) {
    int rbits = num_bits(entries);
    if (slen - i < rbits) {
      printf("ERROR, %d bits undecoded.\n", slen - i);
      break;
    }
    
    value = 0;
    for (int j = i; j < i + rbits; j++) {
      value *= 2;
      value += S[j] - '0';
    }

    string curr = "", tmp;
    if (MIS.find(value) != MIS.end()) {
      curr = MIS[value];
      printf("decoded:   %7d (%s) ", value, curr.c_str());
      printf("[");
      for (int j = i;  j < i + rbits; j++) {
	printf("%c", S[j]);
      }
      printf("]\n");

      T += curr;
      tmp = previous + curr[0]; // first char
      previous = curr;
      if (i != 0) {
	printf("new entry: %7d (%s)\n", entries, tmp.c_str());
	MSI[tmp] = entries;
	MIS[entries] = tmp;
	entries++;
      }

    }
    else {
      printf("cScSc SPECIAL CASE\n");
      curr = previous + previous[0];
      T += curr;
      MSI[curr] = entries;
      MIS[entries] = curr;
      entries++;
      previous = curr;

    }
    i += rbits;    
  }
  
  printf("\nDictionary\n");
  for (map<int, string>::iterator it  = MIS.begin(); it != MIS.end(); it++) {
    printf("%3d: %s\n", it->first, it->second.c_str());
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return -1;
  }
  FILE *fin1 = fopen(argv[1], "r");
  FILE *fin2 = fopen(argv[2], "r");

  if (fin1 == NULL || fin2 == NULL) {
    fprintf(stderr, "Input file %s or %s could not be opened.\n", 
	    argv[1], argv[2]);
    return -1;
  }

  FILE *fout1 = fopen(fname1, "w");

  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);

  // read alphabet
  char* A = new char[ALPHABET_BUFFER_SIZE];
  int alen = fread(A, sizeof(char), ALPHABET_BUFFER_SIZE, fin2);
  
  printf("The alphabet: ");
  for (int i = 0; i < alen; i++) {
    printf("%c", A[i]);
    if (i != alen-1) 
      printf(", ");
    else 
      printf("\n");
  }

  printf("Lempel-Ziv-Welch decoding...\n");
  string T;
  LZW_decoder(A, alen, S, slen, T);

  printf("%s\n", T.c_str());  
  // fout1
  fwrite(T.c_str(), sizeof(char), T.length(), fout1);
}
