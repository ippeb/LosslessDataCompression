#!/bin/bash
# set -v # Echoes all commands before executing.
g++ -Wall -O2 RLE_encoder.cc -o rle_encoder
g++ -Wall -O2 RLE_decoder.cc -o rle_decoder
./rle_encoder ../samples/zero_one_sample.txt > /dev/null
./rle_decoder RLE_encoded.txt > /dev/null
DIFF=$(diff RLE_decoded.txt ../samples/zero_one_sample.txt)
# set +v # Command echoing off.

if [ "$DIFF" != "" ] 
then
    echo "FALSE"
else
    echo "CORRECT"
fi

rm rle_encoder rle_decoder RLE_encoded.txt RLE_decoded.txt