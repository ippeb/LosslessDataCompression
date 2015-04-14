# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

BiN = produce_all_ascii_sample produce_alphabet alphabet_conversion

all: $(BIN)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $<

% : %.o
	$(CXX) -o $@ -c $<

mostlyclean:
	-rm -f *.o 
	-rm -f $(BIN) 

clean: mostlyclean
	-rm -f all_ascii_large.txt

.PHONY: clean mostlyclean allclean:
