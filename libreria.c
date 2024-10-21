#include "libreria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int LINE_LENGTH = 1024;

/**
 * Prints the first N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int head(int N) {
    size_t len = LINE_LENGTH;
    char * buffer;
    int i;

    // Allocate memory for the buffer
    buffer = (char *) malloc(len);

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
    size_t len = LINE_LENGTH;
    char ** data;
    char * buffer;
    int count = 0;
    int i, worstLine, worstLineIndex;

    // Allocate memory for the data storage
    data = (char **) malloc(N * sizeof(char *));
    for (i = 0; i < N; i++) {
        data[i] = (char *) malloc(len);
    }

    // Allocate memory for the buffer
    buffer = (char *) malloc(len);

    // Iterate over the stdin
    while (getline(&buffer, &len, stdin) != EOF) {
        // Get current line length
        int lineLength = strlen(buffer);

        printf("Buffer: %s\n", buffer);
        printf("Size: %d\n\n", lineLength);
        
        // Add the line if the data storage isn't full yet
        if (count < N) {
            printf("Buffer: %s", buffer);
            strcpy(data[count], buffer);
            count++;
        
        // Check if the new line is better than the worst line
        } else {
            // Initialize "worst" variables
            worstLine = strlen(data[0]);
            worstLineIndex = 0;

            // Iterate over the rest of the data and update "worst" variables
            for (i = 1; i < N; i++) {
                if (strlen(data[i]) < worstLine) {
                    worstLine = strlen(data[i]);
                    worstLineIndex = i;
                }
            }

            // Check if the current line is better than the worst one
            if (lineLength > worstLine) {
                strcpy(data[worstLineIndex], buffer);
            }
        }
    }

    // Print data and free lines allocated memory
    for (i = 0; i < N; i++) {
        printf("%s", data[i]);
        free(data[i]);
    }

    // Free previous allocated memory
    free(data);
    free(buffer);

    return 0;
}