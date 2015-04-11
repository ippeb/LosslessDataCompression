#!/bin/bash
make > /dev/null

array=("single_one.txt" "single_zero.txt" "zero_one_sample.txt")
for i in "${array[@]}"
do 
    ./rle_encoder "../samples/"$i > /dev/null
    ./rle_decoder "RLE_encoded.txt" > /dev/null

    DIFF=$(diff RLE_decoded.txt "../samples/"$i)
    if [ -r RLE_decoded.txt ] && [ -r "../samples/"$i ] && [ "$DIFF" == "" ] 
    then
	echo $i "CORRECT"
    else
	echo $i "FALSE"
    fi
done

make clean > /dev/null