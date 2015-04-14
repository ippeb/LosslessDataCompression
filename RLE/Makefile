# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

BIN = RLE_encoder RLE_decoder

all: $(BIN)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $<

% : %.o
	$(CXX) -o $@ -c $<

mostlyclean:
	-rm -f *.o 
	-rm -f $(BIN) 

clean: mostlyclean
	rm -f RLE_encoded.txt RLE_decoded.txt
