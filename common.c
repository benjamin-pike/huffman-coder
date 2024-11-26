#include "types.h"
#include <stdlib.h>
#include <string.h>

HuffmanNode* create_node(uint8_t byte, int frequency) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->byte = byte;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

int compare_nodes(const void *a, const void *b) {
    return (*(HuffmanNode **)a)->frequency - (*(HuffmanNode **)b)->frequency;
}

HuffmanNode* build_huffman_tree(const int *frequency_table) {
    HuffmanNode *nodes[BYTE_RANGE];
    int count = 0;

    for (int i = 0; i < BYTE_RANGE; i++) {
        if (frequency_table[i] > 0) {
            nodes[count++] = create_node(i, frequency_table[i]);
        }
    }

    while (count > 1) {
        qsort(nodes, count, sizeof(HuffmanNode *), compare_nodes);
        HuffmanNode *left = nodes[0];
        HuffmanNode *right = nodes[1];

        HuffmanNode *parent = create_node(0, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        nodes[1] = parent;
        memmove(&nodes[0], &nodes[1], (--count) * sizeof(HuffmanNode *));
    }
    return nodes[0];
}

void free_huffman_tree(HuffmanNode *root) {
    if (!root) return;
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}
