#!/bin/bash
make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt" 
    "all_ascii_small.txt" "all_ascii_large.txt" "star_wars_episode_1.txt")
for i in "${array[@]}"
do 
    ./HUFFMAN_encoder "../samples/"$i > /dev/null
    ./HUFFMAN_decoder HUFFMAN_encoded.txt HUFFMAN_code_words_mapping.txt > /dev/null

    DIFF=$(diff HUFFMAN_decoded.txt "../samples/"$i)
    if [ -r HUFFMAN_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	echo $i "CORRECT"
    else
	echo $i "FALSE"
    fi
done

make clean > /dev/null