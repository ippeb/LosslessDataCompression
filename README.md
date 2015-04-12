Lossless Data Compression
===============

A collection of lossless data compression techniques.


### Lempel-Ziv-Welch (LZW)
A dictionary coder. 

* No dictionary needs to be sent with the encoded data, the decoder rebuilds the dictionary from the encoded data.

### Run-Length Encoding (RLE)
Compresses sequences in which the same character occurs multiple times consecutively. 

* No dictionary needs to be sent with the encoded data.

### Huffman Coding
An entropy coder.

* A dictionary needs to be sent with the encoded data.