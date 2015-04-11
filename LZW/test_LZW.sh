#!/bin/bash
make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt" 
    "all_ascii_small.txt" "all_ascii_large.txt" "star_wars_episode_1.txt")
for i in "${array[@]}"
do 
    ./LZW_encoder "../samples/"$i > /dev/null
    ./LZW_decoder LZW_encoded.txt LZW_alphabet.txt > /dev/null

    DIFF=$(diff LZW_decoded.txt "../samples/"$i)
    if [ -r LZW_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	echo $i "CORRECT"
    else
	echo $i "FALSE"
    fi
done

make clean > /dev/null