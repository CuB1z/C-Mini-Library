#include "libreria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

const int LINE_LENGTH = 1024;

/**
 * Prints the first N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int head(int N) {
    size_t len = LINE_LENGTH;
    char * buffer;
    int i, readBytes;

    // Allocate memory for the buffer
    buffer = (char *) malloc(len);

    for (i = 0; i < N; i++) {
        // Read a line from stdin
        readBytes = getline(&buffer, &len, stdin);
        
        // Handle getline errors
        if (readBytes == -1) {
            fprintf(stderr, "Error reading line %d\n", i + 1);
            return 1;
        }

        // Print the line
        fprintf(stdout, "%s", buffer);
    }
    free(buffer);
    return 0;
}

/**
 * Prints the last N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int tail(int N) {
    size_t len = LINE_LENGTH;
    char ** data;
    char * buffer;
    int i, current = 0;

    // Allocate memory for the data storage
    data = (char **) malloc(N * sizeof(char *));
    for (i = 0; i < N; i++) {
        data[i] = (char *) malloc(len);
    }

    // Allocate memory for the buffer
    buffer = (char *) malloc(len);

    // Iterate over the stdin and save the last N lines
    while (getline(&buffer, &len, stdin) != EOF) {
        // Copy the line to the allocated memory
        strcpy(data[current], buffer);

        // Add the line if the list isn't full yet
        if (current < N - 1) {
            current++;
        } else {
            current = 0;
        }
    }

    // Print the data and free lines allocated memory
    for (i = 0; i < N; i++) {
        fprintf(stdout, "%s", data[current]);

        // Free line allocated memory
        free(data[current]);

        // Update current index
        current++;

        // Reset current index if it reaches the end
        if (current == N) {
            current = 0;
        }
    }

    // Free previous allocated memory
    free(data);
    free(buffer);

    return 0;
}

/**
 * Compares two strings by their length.
 * @param a First string.
 * @param b Second string.
 * @return 0 if the strings have the same length, a positive number if the first string is longer, and a negative number if the second string is longer.
 */
int compareStringsByLength(const void * a, const void * b) {
    return strlen(*(char **)b) - strlen(*(char **)a);
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
    int * lengths;
    int count = 0;
    int i, worstLine, worstLineIndex, lineLength;

    // Allocate memory for the lengths storage
    lengths = (int *) malloc(N * sizeof(int));

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
        lineLength = strlen(buffer);
        
        // Add the line if the data storage isn't full yet
        if (count < N) {
            strcpy(data[count], buffer);
            lengths[count] = lineLength;
            count++;
        
        // Check if the new line is better than the worst line
        } else {
            // Initialize "worst" variables
            worstLine = lengths[0];
            worstLineIndex = 0;

            // Iterate over the rest of the data and update "worst" variables
            for (i = 1; i < N; i++) {
                if (lengths[i] < worstLine) {
                    worstLine = lengths[i];
                    worstLineIndex = i;
                }
            }

            // Check if the current line is better than the worst one
            if (lineLength > worstLine) {
                strcpy(data[worstLineIndex], buffer);
                lengths[worstLineIndex] = lineLength;
            }
        }
    }

    // Sort the data using QuickSort and the compareStringsByLength function
    qsort(data, N, sizeof(char *), compareStringsByLength);

    // Print data and free lines allocated memory
    for (i = 0; i < N; i++) {
        fprintf(stdout, "%s", data[i]);
        free(data[i]);
    }

    // Free previous allocated memory
    free(data);
    free(buffer);

    return 0;
}