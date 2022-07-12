#include <stdio.h>
#include <stdlib.h>
#include "src/interpreter.h"

int main(int argc, char *argv[]) {
    // Checking arguments
    if (argc != 2) {
        fprintf(stderr, "Error: Usage: ./interpreter <path/to/file>\n");
        exit(EXIT_FAILURE);
    }

    // Opening file
    FILE *file = fopen(argv[1], "r");

    // Checking is file could be opened
    if (file == NULL) {
        fprintf(stderr, "Error: Failed to open file \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Reading file  
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *code = malloc(size + 1);

    // Checking is memory could be allocated for file content
    if (code == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for file content\n");
        exit(EXIT_FAILURE);
    }

    // Reading file content and checking errors
    if (fread(code, 1, size, file) != (size_t)size) {
        fprintf(stderr, "Error: Failed to read file content from \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Closing file  
    fclose(file);

    // Assuring that file content is null-terminated
    code[size] = '\0';

    // Running code
    run(code);

    // Freeing memory
    free(code);

    return EXIT_SUCCESS;
}
