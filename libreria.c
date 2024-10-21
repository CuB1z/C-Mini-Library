#include "libreria.h"
#include <stdlib.h>
#include <stdio.h>

const int LINE_LENGTH = 1024;

/**
 * Prints the first N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int head(int N) {
    char * buffer;

    // Allocate memory for the buffer
    size_t len = LINE_LENGTH;
    buffer = (char *) malloc(len);

    int i;
    for (i = 0; i < N; i++) {
        // Read a line from stdin
        int readBytes = getline(&buffer, &len, stdin);
        
        // Handle getline errors
        if (readBytes == -1) {
            fprintf(stderr, "Error reading line %d\n", i + 1);
            return 1;
        }

        // Print the line
        fprintf(stdout, "%s", buffer);
    }

    return 0;
}

/**
 * Prints the last N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int tail(int N) {
    printf("Executed tail %d\n", N);
    return 0;
}

/**
 * Prints the longest N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int longlines(int N) {
    printf("Executed longlines %d\n", N);
    return 0;
}