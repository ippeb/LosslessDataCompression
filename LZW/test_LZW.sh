#!/bin/bash
make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt" 
    "all_ascii_small.txt" "all_ascii_large.txt" "star_wars_episode_1.txt" 
    "single_char_large.txt")

printf "%30s %10s %10s -> %10s\n" "file_name" "state" "test_size" "enc_size "
echo "------------------------------------------------------------------"

for i in "${array[@]}"
do 
    ./LZW_encoder "../samples/"$i > /dev/null
    ./LZW_decoder LZW_encoded.txt LZW_alphabet.txt > /dev/null
    DIFF=$(diff LZW_decoded.txt "../samples/"$i)

    if [ -r LZW_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	originalsize=$(wc -c < "../samples/"$i)
	encodedsize=$(wc -c < "LZW_encoded.txt")
	printf "%30s %10s %10s -> %10s\n" $i "CORRECT" $originalsize $encodedsize
    else
	printf "%30s %10s %10s -> %10s\n" $i "FALSE" "N/A" "N/A"
    fi
done

make clean > /dev/null