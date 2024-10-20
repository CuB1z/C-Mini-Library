#!/bin/bash

# Define the build and output directories
BUILD_DIR=./build
OUTPUT_DIR=./

# Define the usage message
USE="Usage: $0 [OPTION]\nOptions:\n  -h, --help\tDisplay this help message."

# Arguments Control
if [ $# -eq 1 ]
then
    if [[ $1 = "-h" ]] || [[ $1 = "--help" ]]
    then
        echo -e $USE
        exit 0
    else
        echo "Error: Invalid argument.\n"
        echo -e $USE
        exit 1
    fi
elif [ $# -gt 1 ]
then
    echo "Error: Unexpected number of arguments."
    echo -e $USE
    exit 1
fi

# Create the build directory if it doesn't exist and delete its contents
mkdir -p "$BUILD_DIR"
rm -f "$BUILD_DIR"/*

# [Library Compilation] ========================================>>
gcc -c -Wall -Werror libreria.c -o "$BUILD_DIR/libreria.o"
ar -rcs "$BUILD_DIR/libreria.a" "$BUILD_DIR/libreria.o"

if [ $? -ne 0 ]
then
    echo "Error: The library failed to compile."
    exit 2
fi

# [Program Compilation] ========================================>>
gcc -c -Wall -Werror test.c -o "$BUILD_DIR/test.o"
gcc "$BUILD_DIR/test.o" "$BUILD_DIR/libreria.a" -o "$OUTPUT_DIR/test"

if [ $? -ne 0 ]
then
    echo "Error: The program failed to compile."
    exit 2
fi

# [Success Message] ============================================>>
echo "The program was compiled successfully."