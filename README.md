# Huffman Encoder/Decoder

This project provides a command-line utility for compressing and decompressing text files using Huffman encoding, an efficient and lossless data compression technique developed by David A. Huffman in 1952. Huffman encoding functions by assigning binary codes to characters according to their frequency in the input text. Characters that appear more frequently are assigned shorter binary codes; less common characters are assigned longer codes. This results in a compact binary representation of the input text that can be decompressed to restore the original text.

## Features
- **Compression**: Converts input text into a compact binary representation based on character frequency. This is a linear process, relying on two passes through the input data, one to build the Huffman tree and another to encode the data.
- **Decompression**: Restores the original text from the compressed file. This is likewise a linear process that requires only one pass through the compressed data, using the Huffman tree stored in the compressed file to decode the binary representation.
- **Testing Suite**: Includes automated tests to verify functionality. The test suite compresses and decompresses text files, comparing the original and decompressed files to ensure data integrity and determine the compression ratio.

## File Overview
- **`main.c`**: Entry point for the program. Provides CLI interface for compression and decompression operations.
- **`encode.c`**: Contains logic for encoding data using Huffman trees and writing compressed files.
- **`decode.c`**: Contains logic for decoding compressed data back into its original form.
- **`common.c`**: Shared utility functions, including Huffman tree creation and memory management.
- **`types.h`**: Header file defining shared data structures and function prototypes.
- **`test.sh`**: Bash script to automate testing of compression and decompression.

## Dependencies
- **C Standard Library**: Used for file handling, memory allocation, and string manipulation.

## Build Instructions
To build the project, use the provided `Makefile`:
```bash
make
```
This will generate an executable named `huffman`.

## Usage
The program supports two modes: compress and decompress.

### Syntax
```bash
./huffman <compress | decompress> <input_file> <output_file>
```

### Examples
#### Compressing a File
```bash
./huffman compress input.txt compressed
```
#### Decompressing a File
```bash
./huffman decompress compressed output.txt
```

### Testing
Run the test suite using the `test.sh` script

```bash
./test.sh
```
This will:

1. Compress and decompress all `.txt` files in the tests directory.
2. Verify that decompressed files match the original input files.
3. Output compression ratios for successful tests.

## Notes
- Compressed files are not human-readable.
- The compression ratio varies depending on the content of the input files.