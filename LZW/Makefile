# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

all: LZW_encoder LZW_decoder

LZW_encoder: LZW_encoder.o
	$(CXX) -o $@ $^ 

LZW_decoder: LZW_decoder.o
	$(CXX) -o $@ $^ 

.PHONY: clean

mostlyclean:
	rm -f *.o 
	rm -f LZW_encoder LZW_decoder

clean:
	rm -f *.o 
	rm -f LZW_encoder LZW_decoder
	rm -f LZW_alphabet.txt LZW_alphabet_C.txt LZW_encoded.txt LZW_decoded.txt

