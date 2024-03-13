//
// Created by yanai on 3/13/24.
//

#include <stdio.h>
#include <string.h>
#include "compress.h"

void binary_to_digits(const char* inputFileName, const char* outputFileName) {

    // Create variables for the files
    // Buffer is used to make sure each byte ( 8 bits ) in the .bin file represents 2 decimal digits
    FILE *inputFile, *outputFile;
    unsigned char buffer;

    // fopen the input file in "read binary" mode and save as variable,  return if variable is NULL
    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return;
    }

    // fopen the output file in "write" mode and save as variable,  return if variable is NULL
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        // Also close the previously opened input file if failed
        fclose(inputFile);
        return;
    }

    while (fread(&buffer, sizeof(unsigned char), 1, inputFile) == 1) {
        // ~ is bitwise NOT, & is bitwise AND
        // >> 4 shifts the bits of buffer to the right by 4 spots
        // Extract the higher-order 4 bits and apply bitwise NOT, then convert back to a digit
        unsigned char highDigit = (~buffer >> 4) & 0x0F;
        // Extract the lower-order 4 bits and apply bitwise NOT, then convert back to a digit
        unsigned char lowDigit = (~buffer) & 0x0F;

        // Write the digits to the output file
        fprintf(outputFile, "%d", highDigit);
        // Check if the lowDigit is a valid digit (0-9) before writing
        if(lowDigit <= 9) {
            fprintf(outputFile, "%d", lowDigit);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

void digits_to_binary(const char* inputFileName, const char* outputFileName) {

    // Create variables for the files
    // Buffer is used to make sure each byte ( 8 bits ) in the .bin file represents 2 decimal digits
    FILE *inputFile, *outputFile;
    unsigned char buffer = 0;
    int digitCount = 0;

    // fopen the input file in "read" mode and save as variable,  return if variable is NULL
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return;
    }

    // fopen the output file in "write binary" mode and save as variable,  return if variable is NULL
    outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        perror("Error opening output file");
        // Also close the previously opened input file if failed
        fclose(inputFile);
        return;
    }

    int c;
    // Go over all characters in the text file, until we reach END OF FILE
    while ((c = fgetc(inputFile)) != EOF) {
        if (c >= '0' && c <= '9') {
            // ~ is bitwise NOT, & is bitwise AND
            // >> 4 shifts the bits of buffer to the right by 4 spots
            // Extract the higher-order 4 bits and apply bitwise NOT, then convert back to a digit
            unsigned char digit = c - '0'; // Convert ASCII character to digit
            unsigned char binaryDigit = ~(digit) & 0x0F; // Apply bitwise NOT and mask lower 4 bits

            if (digitCount % 2 == 0) {
                buffer = binaryDigit << 4; // Place the digit in the high-order 4 bits if it's the first digit
            } else {
                buffer |= binaryDigit; // Place the digit in the low-order 4 bits if it's the second digit
                fputc(buffer, outputFile); // Write the buffer to the output file
            }

            digitCount++;
        }
    }

    // If there's an odd digit, write the last digit (padded with 4 high-order 0 bits)
    if (digitCount % 2 != 0) {
        fputc(buffer, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}
