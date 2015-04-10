Lempel-Ziv-Welch (LZW)
===============

Test Script
----------
```
bash -x test_LZW.sh 
```

Sample Usage
----------
```
g++ -Wall -O2 LZW_encoder.cc -o lzw_encoder
g++ -Wall -O2 LZW_decoder.cc -o lzw_decoder
./lzw_encoder ../samples/star_wars_episode_1.txt
./lzw_decoder LZW_encoded.txt LZW_alphabet.txt
```

