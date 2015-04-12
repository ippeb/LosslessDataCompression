# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

all: produce_all_ascii_sample produce_alphabet

produce_all_ascii_sample: produce_all_ascii_sample.o
	$(CXX) -o $@ $^ 

produce_alphabet: produce_alphabet.o
	$(CXX) -o $@ $^ 

.PHONY: clean

clean:
	rm -f *.o 
	rm -f produce_all_ascii_sample produce_alphabet 
	rm -f all_ascii_large.txt


