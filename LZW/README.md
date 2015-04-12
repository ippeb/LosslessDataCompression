Lempel-Ziv-Welch (LZW)
===============

Test Script
----------
```
bash test_LZW.sh 
```

Sample Usage
----------
```
make
./LZW_encoder ../samples/mapreduce.pdf
./LZW_decoder LZW_encoded.txt LZW_alphabet.txt
```


Fast Lempel-Ziv-Welch (LZW)
===============

Test Script
----------
```
bash test_fast_LZW.sh 
```

Sample Usage
----------
```
make
./LZW_fast_encoder ../samples/mapreduce.pdf
./LZW_fast_decoder LZW_encoded.fastlzw
```


