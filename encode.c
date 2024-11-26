#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_codes(HuffmanNode *root, HuffmanCode *codes, uint8_t *buffer, size_t depth) {
    if (!root->left && !root->right) {
        codes[root->byte].code = (uint8_t *)malloc(depth);
        codes[root->byte].length = depth;
        memcpy(codes[root->byte].code, buffer, depth);
        return;
    }
    if (root->left) {
        buffer[depth] = 0;
        generate_codes(root->left, codes, buffer, depth + 1);
    }
    if (root->right) {
        buffer[depth] = 1;
        generate_codes(root->right, codes, buffer, depth + 1);
    }
}

void encode_data(const uint8_t *data, size_t length, HuffmanCode *codes, uint8_t **compressed, size_t *compressed_size_bits) {
    size_t bit_index = 0;
    *compressed = (uint8_t *)malloc((length * 8 + 7) / 8);

    for (size_t i = 0; i < length; i++) {
        HuffmanCode code = codes[data[i]];
        for (size_t j = 0; j < code.length; j++) {
            if (code.code[j]) {
                (*compressed)[bit_index / 8] |= (1 << (7 - (bit_index % 8)));
            }
            bit_index++;
        }
    }
    *compressed_size_bits = bit_index;
}

void compress_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Failed to open input file");
        exit(1);
    }

    fseek(in, 0, SEEK_END);
    size_t length = ftell(in);
    rewind(in);

    uint8_t *data = (uint8_t *)malloc(length);
    fread(data, 1, length, in);
    fclose(in);

    int frequency_table[BYTE_RANGE] = {0};
    for (size_t i = 0; i < length; i++) {
        frequency_table[data[i]]++;
    }

    HuffmanNode *root = build_huffman_tree(frequency_table);

    HuffmanCode codes[BYTE_RANGE] = {0};
    uint8_t buffer[BYTE_RANGE] = {0};
    generate_codes(root, codes, buffer, 0);

    uint8_t *compressed = NULL;
    size_t compressed_size_bits = 0;
    encode_data(data, length, codes, &compressed, &compressed_size_bits);

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        perror("Failed to open output file");
        free(data);
        free(compressed);
        free_huffman_tree(root);
        exit(1);
    }

    fwrite(frequency_table, sizeof(int), BYTE_RANGE, out);
    fwrite(&compressed_size_bits, sizeof(size_t), 1, out);
    fwrite(compressed, 1, (compressed_size_bits + 7) / 8, out);

    fclose(out);

    free(data);
    free(compressed);
    free_huffman_tree(root);

    printf("Compression complete. Output saved to %s\n", output_file);
}
