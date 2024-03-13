//
// Created by yanai on 3/13/24.
//

#include <stdio.h>
#include <string.h>
#include "compress.h"

int main(int argc, char *argv[]){

    // Make sure exactly 3 arguments were given (executable name, -c or -d, file.txt or file.bin
    if (argc != 3) {
        printf("Usage: %s (-c or -d) (file.txt or file.bin)\n", argv[0]);
        return 1;
    }

    // Initialize variables: opt (-c or -d), file - file path, file_type for file's extension, output_file
    char *opt = argv[1];
    char *file = argv[2];
    char *file_type = strrchr(file, '.');
    const char *output_file;

    // If opt is not one od the 2 options, (-c or -d), Show message and return 1
    if (strcmp(opt, "-c") != 0 && strcmp(opt, "-d") != 0) {
        printf("Invalid option. Use either -c or -d.\n");
        return 1;
    }

    // Make sure -c option gets a text file and -d option gets a binary file
    if ((strcmp(opt, "-c") == 0 && strcmp(file_type, ".txt") != 0) ||
        (strcmp(opt, "-d") == 0 && strcmp(file_type, ".bin") != 0)) {
        printf("Extension doesn't match the chosen option.\n");
        return 1;
    }

    // Print info
    printf("Option: %s\n", opt);
    printf("Input File: %s\n", file);
    printf("Extension: %s\n", file_type);

    // Call the correct function according to opt
    if (strcmp(opt, "-c") == 0) {
        output_file = "encodedOutput.bin";
        digits_to_binary(file, output_file);
    } else if (strcmp(opt, "-d") == 0) {
        output_file = "decodedOutput.txt";
        binary_to_digits(file, output_file);
    }

    return 0;
}
