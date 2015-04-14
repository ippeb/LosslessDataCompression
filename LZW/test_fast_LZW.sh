#!/bin/bash

#==============================================================================
# Tests the Lempel-Ziw-Welch Encoder and Decoder.
#
# Author: Josef Ziegler (ippeb24@gmail.com)
#==============================================================================

make > /dev/null

array=(../samples/*)

printf "%40s %10s %10s -> %10s (%10s)\n" "file_name" "state" "orig_size" "enc_size" "diff_size"
echo "------------------------------------------------------------------------------------------"

for i in "${array[@]}"
do 
    ./LZW_fast_encoder $i > /dev/null
    ./LZW_fast_decoder LZW_encoded.fastlzw  > /dev/null
    DIFF=$(diff LZW_decoded.txt $i)

    if [ -r LZW_decoded.txt ] && [ -r $i ] && [ "$DIFF" == "" ] 
    then
	originalsize=$(wc -c < $i)
	encodedsize=$(wc -c < "LZW_encoded.fastlzw")
	diffsize=`expr $originalsize - $encodedsize`
	printf "%40s %10s %10s -> %10s (%10s)\n" $i "CORRECT" $originalsize $encodedsize $diffsize
    else
	printf "%40s %10s %10s -> %10s (%10s)\n" $i "FALSE" "N/A" "N/A" "N/A"
    fi
done

make clean > /dev/null