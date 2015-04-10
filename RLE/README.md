Run-Length Encoding (RLE)
===============

Test Script
----------
```
bash -x test_RLE.sh 
```

Sample Usage
----------
```
g++ -Wall -O2 RLE_encoder.cc -o rle_encoder
g++ -Wall -O2 RLE_decoder.cc -o rle_decoder
./rle_encoder ../samples/zero_one_sample.txt
./rle_decoder RLE_encoded.txt 
```

