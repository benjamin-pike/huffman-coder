#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void decode_data(const uint8_t *compressed, size_t compressed_size_bits, HuffmanNode *root, uint8_t **decompressed, size_t *decompressed_size) {
    size_t bit_index = 0, decoded_index = 0;
    HuffmanNode *current = root;

    *decompressed = (uint8_t *)malloc(compressed_size_bits);

    while (bit_index < compressed_size_bits) {
        int bit = (compressed[bit_index / 8] >> (7 - (bit_index % 8))) & 1;
        current = bit == 0 ? current->left : current->right;

        if (!current->left && !current->right) {
            (*decompressed)[decoded_index++] = current->byte;
            current = root;
        }
        bit_index++;
    }
    *decompressed_size = decoded_index;
}

void decompress_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Failed to open input file");
        exit(1);
    }

    int frequency_table[BYTE_RANGE] = {0};
    fread(frequency_table, sizeof(int), BYTE_RANGE, in);

    HuffmanNode *root = build_huffman_tree(frequency_table);

    size_t compressed_size_bits;
    fread(&compressed_size_bits, sizeof(size_t), 1, in);

    size_t compressed_size_bytes = (compressed_size_bits + 7) / 8;
    uint8_t *compressed = (uint8_t *)malloc(compressed_size_bytes);
    fread(compressed, 1, compressed_size_bytes, in);
    fclose(in);

    uint8_t *decompressed = NULL;
    size_t decompressed_size = 0;
    decode_data(compressed, compressed_size_bits, root, &decompressed, &decompressed_size);

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        perror("Failed to open output file");
        free(compressed);
        free(decompressed);
        free_huffman_tree(root);
        exit(1);
    }
    fwrite(decompressed, 1, decompressed_size, out);
    fclose(out);

    free(compressed);
    free(decompressed);
    free_huffman_tree(root);

    printf("Decompression complete. Output saved to %s\n", output_file);
}
