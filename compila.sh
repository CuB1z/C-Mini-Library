#!/bin/bash

# Define the build and output directories
BUILD_DIR=./build
OUTPUT_DIR=./

# Create the build directory if it doesn't exist and empty it
mkdir -p "$BUILD_DIR"
rm -f "$BUILD_DIR"/*

# Compile the library
gcc -c -Wall -Werror libreria.c -o "$BUILD_DIR/libreria.o"
ar -rcs "$BUILD_DIR/libreria.a" "$BUILD_DIR/libreria.o"

# Compile the program
gcc -c -Wall -Werror test.c -o "$BUILD_DIR/test.o"
gcc "$BUILD_DIR/test.o" "$BUILD_DIR/libreria.a" -o "$OUTPUT_DIR/test"