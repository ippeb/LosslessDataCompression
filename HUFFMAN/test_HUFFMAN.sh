#!/bin/bash

#==============================================================================
# Tests the Huffman Encoder and Huffman Decoder.
#
# Author: Josef Ziegler (ippeb24@gmail.com)
#==============================================================================

make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt" 
    "all_ascii_small.txt" "all_ascii_large.txt" "star_wars_episode_1.txt" 
    "single_char_large.txt")

printf "%30s %10s %10s -> %10s (%10s)\n" "file_name" "state" "test_size" "enc_size" "mapping_size"
echo "--------------------------------------------------------------------------------"

for i in "${array[@]}"
do 
    ./HUFFMAN_encoder "../samples/"$i > /dev/null
    ./HUFFMAN_decoder HUFFMAN_encoded.txt HUFFMAN_code_words_mapping.txt > /dev/null
    DIFF=$(diff HUFFMAN_decoded.txt "../samples/"$i)

    if [ -r HUFFMAN_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	originalsize=$(wc -c < "../samples/"$i)
	encodedsize=$(wc -c < "HUFFMAN_encoded.txt")
	mappingsize=$(wc -c < "HUFFMAN_code_words.txt")
	printf "%30s %10s %10s -> %10s (%10s)\n" $i "CORRECT" $originalsize $encodedsize $mappingsize
    else
	printf "%30s %10s %10s -> %10s (%10s)\n" $i "FALSE" "N/A" "N/A" "N/A"
    fi
done

make clean > /dev/null