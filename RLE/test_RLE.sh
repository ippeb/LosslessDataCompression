#!/bin/bash
make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt"
    "single_char_large.txt")

printf "%30s %10s %10s -> %10s\n" "file_name" "passed_test" "test_size" "enc_size "
echo "------------------------------------------------------------------"

for i in "${array[@]}"
do 
    ./RLE_encoder "../samples/"$i > /dev/null
    ./RLE_decoder "RLE_encoded.txt" > /dev/null
    DIFF=$(diff RLE_decoded.txt "../samples/"$i)

    if [ -r RLE_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	originalsize=$(wc -c < "../samples/"$i)
	encodedsize=$(wc -c < "RLE_encoded.txt")
	printf "%30s %10s %10s -> %10s\n" $i "CORRECT" $originalsize $encodedsize
    else
	printf "%30s %10s %10s -> %10s\n" $i "FALSE" "N/A" "N/A"
    fi
done

make clean > /dev/null