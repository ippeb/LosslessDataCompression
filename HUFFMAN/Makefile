# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

all: HUFFMAN_encoder HUFFMAN_decoder

HUFFMAN_encoder: HUFFMAN_encoder.o
	$(CXX) -o $@ $^ 

HUFFMAN_decoder: HUFFMAN_decoder.o
	$(CXX) -o $@ $^ 

.PHONY: clean

mostlyclean:
	rm -f *.o 
	rm -f HUFFMAN_encoder HUFFMAN_decoder

clean:
	rm -f *.o 
	rm -f HUFFMAN_encoder HUFFMAN_decoder
	rm -f HUFFMAN_alphabet.txt HUFFMAN_code_words.txt HUFFMAN_code_words_C.txt HUFFMAN_encoded.txt HUFFMAN_code_words_mapping.txt HUFFMAN_alphabet.txt HUFFMAN_decoded.txt

