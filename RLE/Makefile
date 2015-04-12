# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

all: RLE_encoder RLE_decoder

RLE_encoder: RLE_encoder.o
	$(CXX) -o $@ $^ 

RLE_decoder: RLE_decoder.o
	$(CXX) -o $@ $^ 

.PHONY: clean

mostlyclean:
	rm -f *.o 
	rm -f RLE_encoder RLE_decoder

clean:
	rm -f *.o 
	rm -f RLE_encoder RLE_decoder
	rm -f RLE_encoded.txt RLE_decoded.txt
