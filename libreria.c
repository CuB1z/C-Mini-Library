#include "libreria.h"
#include <stdio.h>

/**
 * Prints the first N lines from stdin.
 * @param N Number of lines to print.
 * @return 0 if the function was executed successfully.
 */
int head(int N) {
    printf("Executed head %d\n", N);
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