/*
  Generate file containing all ASCII chars.

  Author: Josef Ziegler (ippeb24@gmail.com)

 */

#include <cstdio>
using namespace std;

int main() {
  FILE *fout = fopen("all_ascii_large.txt", "w");
  for (int j = 0; j < 4*4*256; j++) {
    for (int i = 0; i < 256; i++) {
      fprintf(fout, "%c", i);
    }
  }
}
