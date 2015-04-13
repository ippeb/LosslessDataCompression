# ------------------------------------------------
# Author: Josef Ziegler (ippeb24@gmail.com)
# ------------------------------------------------
CXX      = @g++
CXXFLAGS = -O2 -Wall -Wextra -pedantic

OBJECTS = LZW_encoder.o LZW_decoder.o LZW_fast_encoder.o LZW_fast_decoder.o

all: $(OBJECTS)

%.o : %.cc
	@echo " CXX " $@
	$(CXX) -o $(*) $<

mostlyclean:
	-rm -f *.o 
	-rm -f LZW_encoder LZW_decoder 
	-rm -f LZW_fast_encoder LZW_fast_decoder

clean:
	-rm -f *.o 
	-rm -f LZW_encoder LZW_decoder
	-rm -f LZW_fast_encoder LZW_fast_decoder 
	-rm -f LZW_alphabet.txt LZW_alphabet_C.txt LZW_encoded.txt LZW_decoded.txt LZW_encoded.fastlzw

.PHONY: clean mostlyclean all