# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# Author: Thomas Richner (mail@trichner.ch)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

BIN = LZW_encoder LZW_decoder LZW_fast_encoder LZW_fast_decoder

all: $(BIN)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $<

% : %.o
	$(CXX) -o $@ -c $<

mostlyclean:
	-rm -f *.o 
	-rm -f $(BIN) 

clean: mostlyclean
	-rm -f LZW_alphabet.txt LZW_alphabet_C.txt LZW_encoded.txt LZW_decoded.txt LZW_encoded.fastlzw

.PHONY: clean mostlyclean all
