Lossless Data Compression
===============

A collection of **lossless** data compression techniques.

## Lempel-Ziv-Welch (LZW)
A dictionary coder. 

Supports any file format, `.txt`, `.jpg`, `.pdf`, `.gif`, `.png`, `.avi`, `.zip`, etc.

### Sample Usage

#### Encoder
Let's compress a pdf file, Jeff's and Sanjay's paper on MapReduce.


```
./LZW/LZW_encoder samples/mapreduce.pdf
```

This produces `LZW_encoded.txt`, the compressed text and `LZW_alphabet.txt`, the set of symbols used in the original input. 

Note, that the compressed  `LZW_encoded.txt` is stored as a text file using only the characters '0' and '1'. In practice, the output would be stored using all 256 symbols of a byte, so the effective size of the compressed output is actually one eight of `LZW_encoded.txt`.

#### Decoder 
To decode the encoded text, simply pass the compressed text and the input alphabet to the decoder.


```
./LZW/LZW_decoder LZW_encoded.txt LZW_alphabet.txt
```

The decoded output is stored in `LZW_decoded.txt`, which should correspond to the original input provided, in this case, `samples/mapreduce.pdf`.

## Run-Length Encoding (RLE)
Compresses sequences in which the same character occurs multiple times consecutively. 

Currently only supports text files containing '0' and '1'.

### Sample Usage

#### Encoder
Running the following line produces `RLE_encoded.txt`, the Run-Length encoded output.


```
./RLE/RLE_encoder samples/zero_one_sample.txt
```

#### Decoder 
To decode the encoded text, simply pass the compressed text to the decoder.


```
./RLE/RLE_decoder RLE_encoded.txt
```

The decoded output is stored in `RLE_decoded.txt`, which should correspond to the original input.


## Huffman Coding
An entropy coder.

Supports any file format, `.txt`, `.jpg`, `.pdf`, `.gif`, `.png`, `.avi`, `.zip`, etc.

### Sample Usage

#### Encoder
Let's compress a picture of a tiger wearing sunglasses.


```
./HUFFMAN/HUFFMAN_encoder samples/deal_with_it.jpg
```

This produces `HUFFMAN_encoded.txt`, the Huffman encoded output and `HUFFMAN_code_words_mapping.txt`, the mapping of symbols to codewords. (Some other files are also produced, you may ignore those.)

Note, that similarly to LZW, the Huffman encoding `HUFFMAN_encoded.txt` is stored as a text file using only the characters '0' and '1'. In practice, the output would be stored using all 256 symbols of a byte, so the effective size of the compressed output is actually one eight of `HUFFMAN_encoded.txt`.


#### Decoder
To decode the encoded text, simply pass the compressed text and the codeword mapping to the decoder.


```
./HUFFMAN/HUFFMAN_decoder HUFFMAN_encoded.txt HUFFMAN_code_words_mapping.txt
```

The decoded output is stored in `HUFFMAN_decoded.txt`. As you can see by running 
`diff HUFFMAN_decoded.txt samples/deal_with_it.jpg`
the decoded output corresponds to our original picture.

