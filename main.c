#include "types.h"
#include <stdio.h>
#include <string.h>

void print_usage(const char *program_name) {
    printf("Usage: %s <compress|decompress> <input_file> <output_file>\n", program_name);
}
int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];

    if (strcmp(mode, "compress") == 0) {
        compress_file(input_file, output_file);
    } else if (strcmp(mode, "decompress") == 0) {
        decompress_file(input_file, output_file);
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
