/*
  Huffman Coding (encoder)
  lossless data compression algorithm, entropy encoding

  The main function takes as argument:
  arg1: input file name, this should be a ASCII-only textfile.

  It then writes the following files:
  fout1: output file name: fname1, 
         contains the Huffman code words.
  fout2: file name: fname2,
         contains the C code for an array containing the
         Huffman code words.
  fout3: file name: fname3,
         input text after every character was substituted
         with the corresponding Huffman code word (binary).
  fout4: file name: fname4,
         contains the mapping of Huffman code words.
	 Essentially, this comprises the alphabet.
	 Characters are saved as integers (according to 
	 the ASCII table). 
  fout5: file name: fname5,
         contains a null-terminated string, containing 
	 all chars of the alphabet.

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#define INPUT_BUFFER_SIZE 10000000
#define ALPHABET_BUFFER_SIZE 1000
const char fname1[] = "HUFFMAN_code_words.txt";
const char fname2[] = "HUFFMAN_code_words_C.txt";
const char fname3[] = "HUFFMAN_encoded.txt";
const char fname4[] = "HUFFMAN_code_words_mapping.txt";
const char fname5[] = "HUFFMAN_alphabet.txt";
using std::vector;
using std::stack;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::greater;

typedef pair<double, int> PDI;
typedef pair<int, bool> PIB;

// A = {a_1, ..., a_n} alphabet, as an array of chars
//   it is assumed that 0 <= a_i <= n-1 and all a_i are
//   distinct, A is terminated with a '0' (C string)
// alen: length of A
// W = {w_1, ..., w_n} set of positive symbol weights,
//   usually proportional to probabilities
// C = {c_1, ..., c_n} the set of binary codeword
//   where c_i is the codeword for a_i, 1 <= i <= n
void HuffmanCoding_encoder(char const * const A, const int alen, double const * const W, vector<vector<bool> >& C) {
  if (alen == 1) {
    C.resize(1);
    C[0].push_back(false);
  }

  int id = alen;
  // format of nodes inserted in priority queue:
  // (weight, node index)
  priority_queue<PDI, vector<PDI>, greater<PDI> > P;
  // add all leaf nodes to the priority queue
  for (int i = 0; i < alen; i++) 
    P.push(make_pair(W[i], i));
  
  // generate the Huffman tree

  // parent[i] = (j, b): the parent of node i is node j
  // and the edge is marked with the binary digit b
  PIB* parent = new PIB[alen + alen - 1];
  while (P.size() > 1) {
    // remove the two nodes of highest priority from the queue
    PDI n1 = P.top();
    P.pop();
    PDI n2 = P.top();
    P.pop();
    // create a new internal node with these two nodes as children
    parent[n1.second] = make_pair(id, 0);
    parent[n2.second] = make_pair(id, 1);
    P.push(make_pair(n1.first + n2.first, id++));
  }
  parent[id-1] = make_pair(-1, 0);

  // construct the code words from the Huffman tree
  stack<bool> tempstack;
  C.resize(alen);
  for (int i = 0; i < alen; i++) {
    int v = i;
    while (parent[v].first != -1) {
      tempstack.push(parent[v].second);
      v = parent[v].first;
    }
    while (!tempstack.empty()) {
      C[i].push_back(tempstack.top());
      tempstack.pop();
    }
  } 
}


int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return 1;
  }
  
  FILE *fin = fopen(argv[1], "r");
  if (fin == NULL) {
    fprintf(stderr, "Input file %s could not be opened.\n", argv[1]);
    return 1;
  }

  FILE *fout1 = fopen(fname1, "w");
  FILE *fout2 = fopen(fname2, "w");
  FILE *fout3 = fopen(fname3, "w");
  FILE *fout4 = fopen(fname4, "w");
  FILE *fout5 = fopen(fname5, "w");
  
  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin);
  // specify the alphabet
  // the alphabet is determined by the chars appearing in the 
  // input, thus, every symbol should appear once in the input
  char* A = new char[ALPHABET_BUFFER_SIZE]; 
  int alen = 0;
  int F[256] = { 0 }; // F[i] counts the frequency of char i
  for (int i = 0; i < slen; i++) {
    if (F[(unsigned char) S[i]] == 0)
      alen++;
    F[(unsigned char) S[i]]++;
  }

  for (int i = 0, j = 0; i < 256; i++) 
    if (F[i] > 0)
      A[j++] = i;
  
  printf("The alphabet: ");
  for (int i = 0; i < alen; i++) {
    printf("%c", A[i]); // TODO: some chars are unprintable
    if (i != alen-1) 
      printf(", ");
    else 
      printf("\n");
  }

  // specify the weights
  double* W = new double[alen];
  for (int i = 0; i < alen; i++) {
    W[i] = (double) F[(unsigned char) A[i]] / (double) slen;
  }

  vector<vector<bool> > C;
  printf("Huffman Coding...\n");
  HuffmanCoding_encoder(A, alen, W, C);

  // print code words
  printf("The code words are:\n");
  for (int i = 0; i < alen; i++) {
    printf("'%c' (%04.1lf) [%d] ", A[i], W[i]*100.0, F[(unsigned char) A[i]]);
    for (vector<bool>::iterator it = C[i].begin(); it != C[i].end(); it++) {
      printf("%d", (int) *it);
    }
    printf("\n");
  }

  // fout2
  fprintf(fout2, "char C[%d][]={", alen);
  for (int i = 0; i < alen; i++) {
    for (vector<bool>::iterator it = C[i].begin(); it != C[i].end(); it++) {
      fprintf(fout2, "%d", (int) *it);
    }
    if (i != alen-1) {
      fprintf(fout2, ",");
    }
  }
  fprintf(fout2, "};\n");

  // fout1
  fprintf(fout1, "%d ",alen);
  for (int i = 0; i < alen; i++) {
    for (vector<bool>::iterator it = C[i].begin(); it != C[i].end(); it++) {
      fprintf(fout1, "%d", (int) *it);
    }
    if (i != alen-1) {
      fprintf(fout1, " ");
    }
  }
  fprintf(fout1, "\n");

  // reverse mapping, A[i] to index
  int R[256];
  memset(R, -1, sizeof R);
  for (int i = 0; i < alen; i++) 
    R[(unsigned char) A[i]] = i;
  // fout3
  for (int i = 0; i < slen; i++) {
    for (vector<bool>::iterator it = C[R[(unsigned char) S[i]]].begin(); 
	 it != C[R[(unsigned char) S[i]]].end(); it++) {
      fprintf(fout3, "%d", (int) *it);
    }
  }
  fprintf(fout3, "\n");

  // fout4
  fprintf(fout4, "%d\n",alen);
  for (int i = 0; i < alen; i++) {
    fprintf(fout4, "%d ", (unsigned char) A[i]);
    for (vector<bool>::iterator it = C[i].begin(); it != C[i].end(); it++) {
      fprintf(fout4, "%d", (int) *it);
    }
    fprintf(fout4, "\n");
  }

  // fout5
  fwrite(A, sizeof(char), alen, fout5);
}
