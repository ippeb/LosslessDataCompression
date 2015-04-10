#!/bin/bash
# set -v # Echoes all commands before executing.
g++ -Wall -O2 HUFFMAN_encoder.cc -o huffman_encoder
g++ -Wall -O2 HUFFMAN_decoder.cc -o huffman_decoder
./huffman_encoder ../samples/star_wars_episode_1.txt > /dev/null
./huffman_decoder huffman_encoded.txt huffman_code_words_mapping.txt > /dev/null
DIFF=$(diff huffman_decoded.txt ../samples/star_wars_episode_1.txt )
# set +v # Command echoing off.

if [ "$DIFF" != "" ] 
then
    echo "FALSE"
else
    echo "CORRECT"
fi

rm huffman_encoder huffman_decoder huffman_alphabet.txt huffman_encoded.txt huffman_code_words.txt huffman_code_words_C.txt huffman_code_words_mapping.txt huffman_decoded.txt 