#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stddef.h>

#define BYTE_RANGE 256

typedef struct HuffmanNode {
    uint8_t byte;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct {
    uint8_t *code;
    size_t length;
} HuffmanCode;

HuffmanNode* build_huffman_tree(const int *frequency_table);
void free_huffman_tree(HuffmanNode *root);

void compress_file(const char *input_file, const char *output_file);
void decompress_file(const char *input_file, const char *output_file);

#endif
