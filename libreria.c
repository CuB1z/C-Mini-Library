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
    free(buffer);
    return 0;
}

/**
 * Prints the last N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int tail(int N) {

    // Declare a structure to store the lines
    struct entry{
        char *line;
        TAILQ_ENTRY(entry) entries;
    };
    
    size_t len = LINE_LENGTH;
    char * buffer;
    int i, count = 0;
    struct entry * item, * aux;

    // Declare a structure to store the head of the list
    TAILQ_HEAD(tailhead, entry) head;

    // Initialize the list
    TAILQ_INIT(&head);

    // Allocate memory for the buffer
    buffer = (char *) malloc(len);

    // Iterate over the stdin
    while (getline(&buffer, &len, stdin) != EOF) {
        // Allocate memory for the read line
        item = (struct entry *) malloc(sizeof(struct entry));
        item->line = (char *) malloc(len);

        // Copy the line to the allocated memory
        strcpy(item->line, buffer);

        // Add the line if the list isn't full yet
        if (count < N) {
            TAILQ_INSERT_TAIL(&head, item, entries);
            count++;
        
        // Remove the first line and add the new one
        } else {
            // Save current head to free memory
            aux = TAILQ_FIRST(&head);

            // Remove the current head
            TAILQ_REMOVE(&head, aux, entries);

            // Add the new line to the queue
            TAILQ_INSERT_TAIL(&head, item, entries);

            // Free the memory of the removed item
            free(aux->line);
            free(aux);
        }

    }
        
    // Print N lines from the list
    TAILQ_FOREACH(item, &head, entries) {
        fprintf(stdout, "%s", item->line);
    }

// Free allocated memory used by the structure data
    for (i = 0; i < N; i++) {
        // Save current head to free memory
        aux = TAILQ_FIRST(&head);

        // Remove the current head
        TAILQ_REMOVE(&head, aux, entries);

        // Add the new line to the queue
        TAILQ_INSERT_TAIL(&head, item, entries);

        // Free the memory of the removed item
        free(aux->line);
        free(aux);
    }

    // Free the buffer memory
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
        
        // Add the line if the data storage isn't full yet
        if (count < N) {
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