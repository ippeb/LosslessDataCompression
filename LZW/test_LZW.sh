#!/bin/bash
set -v # Echoes all commands before executing.
g++ -Wall -O2 LZW_encoder.cc -o lzw_encoder
g++ -Wall -O2 LZW_decoder.cc -o lzw_decoder
./lzw_encoder ../star_wars_episode_1.txt > /dev/null
./lzw_decoder LZW_encoded.txt LZW_alphabet.txt > /dev/null
DIFF=$(diff LZW_decoded.txt ../star_wars_episode_1.txt)
set +v # Command echoing off.

if [ "$DIFF" != "" ] 
then
    echo "FALSE"
else
    echo "CORRECT"
fi
