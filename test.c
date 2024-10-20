#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
const char * FLAGS[] = { "-head", "-tail", "-longlines" };
char * USAGE = "Usage: %s [%s | %s | %s] [lines number (OPTIONAL)]\n";
int DEFAULT_LINES = 10;

int main(int argc, char * argv[]) {
    // Initialize variables
    int n = DEFAULT_LINES;
    char * selection = "";

    // Arguments Control
    if (argc == 3) {
        selection = argv[1];
        n = atoi(argv[2]);
    } else if (argc == 2) {
        selection = argv[1];
    } else {
        fprintf(stderr, "Error. Invalid number of arguments.\n");
        fprintf(stderr, USAGE, argv[0], FLAGS[0], FLAGS[1], FLAGS[2]);
        return 1;
    }

    // Selection Control
    int result = 0;
    if (strcmp(selection, FLAGS[0]) == 0) {
        result = head(n);
    } else if (strcmp(selection, FLAGS[1]) == 0) {
        result = tail(n);
    } else if (strcmp(selection, FLAGS[2]) == 0) {
        result = longlines(n);
    } else {
        fprintf(stderr, "Error. Invalid selection.\n");
        fprintf(stderr, USAGE, argv[0], FLAGS[0], FLAGS[1], FLAGS[2]);
        return 1;
    }

    // Print execution result
    if (result != 0) {
        fprintf(stderr, "Error. Something went wrong.\n");
        return 2;
    }

    return 0;
}