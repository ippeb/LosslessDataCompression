# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

BIN = HUFFMAN_encoder HUFFMAN_decoder

all: $(BIN)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $<

% : %.o
	$(CXX) -o $@ -c $<

mostlyclean:
	-rm -f *.o 
	-rm -f $(BIN) 

clean: mostlyclean
	rm -f HUFFMAN_alphabet.txt HUFFMAN_code_words.txt HUFFMAN_code_words_C.txt HUFFMAN_encoded.txt HUFFMAN_code_words_mapping.txt HUFFMAN_alphabet.txt HUFFMAN_decoded.txt

