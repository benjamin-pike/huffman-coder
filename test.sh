#!/bin/bash
TEST_DIR="tests"
COMPRESSED_FILE="compressed"
DECOMPRESSED_FILE="decompressed.txt"

INPUT_FILES=($(find "$TEST_DIR" -type f -name "*.txt"))

echo "----- Running tests -----"
for INPUT_FILE in "${INPUT_FILES[@]}"; do
    ./huffman compress "$INPUT_FILE" "$COMPRESSED_FILE" > /dev/null 2>&1
    ./huffman decompress "$COMPRESSED_FILE" "$DECOMPRESSED_FILE" > /dev/null 2>&1

    if cmp -s "$INPUT_FILE" "$DECOMPRESSED_FILE"; then
        INPUT_SIZE=$(stat -f%z "$INPUT_FILE")
        COMPRESSED_SIZE=$(stat -f%z "$COMPRESSED_FILE")

        if [ "$INPUT_SIZE" -ne 0 ]; then
            COMPRESSION_RATIO=$(echo "scale=3; $COMPRESSED_SIZE / $INPUT_SIZE" | bc)
        else
            COMPRESSION_RATIO="N/A"
        fi

        echo "PASS: $(basename "$INPUT_FILE") successfully compressed and decompressed - ratio: 0$COMPRESSION_RATIO"
    else
        echo "FAIL: $(basename "$INPUT_FILE") did not match after decompression."
        echo "----- Exiting -----"
        rm -f $COMPRESSED_FILE $DECOMPRESSED_FILE
        exit 1
    fi

    rm -f $COMPRESSED_FILE $DECOMPRESSED_FILE
done

echo "----- All tests passed -----"
