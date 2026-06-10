/*
 * This program accepts a positive integer 'n' and a list of files as command-line arguments.
 * Uses 'fseek' to jump directly to the n-th character (offset n-1) from the start of each file.
 * Reads the character at that position and prints its decimal ASCII code to stdout.
 * Counts every byte in the file as a valid character position, including all whitespaces.
 * Safely prints descriptive errors to stderr if a file is missing or too short to read.
* Name: Ido Sheffi
* ID: 208138974
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "seek.h" /* header file with the function prototype */

int main(int argc, char *argv[]) {
    long n;
    int i;

    /* FATAL ERROR: Check argument count (Program name + n + at least 1 file = 3) */
    if (argc < 3) {
        fprintf(stderr, "Error: Not enough arguments.\n");
        fprintf(stderr, "Usage: %s <positive integer n> <file1> [file2...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* FATAL ERROR: Validate that argv[1] is entirely digits */
    for (i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            fprintf(stderr, "Error: The first argument must be a positive integer.\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Convert the validated string to a long integer */
    n = atol(argv[1]);

    /* Ensure it is strictly greater than 0 */
    if (n <= 0) {
        fprintf(stderr, "Error: The target sequence (n) must be strictly greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    /* LOOP: Process each file provided in the command line */
    for (i = 2; i < argc; i++) {
        process_file(argv[i], n);
    }

    return 0;
}

/* =========================================================================
 * FUNCTION: process_file
 * Purpose: Opens the file, seeks to the n-th character, and prints its ASCII value.
 * ========================================================================= */
void process_file(const char *filename, long n) {
    int ch;
    FILE *fp;

    /* Attempt to open the file in read mode */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        /* Non-fatal error: Print and return to the main loop */
        fprintf(stderr, "Error: Cannot open file '%s'.\n", filename);
        return;
    }

    /* Jump to the n-th character (offset n - 1) */
    /* fseek returns 0 on success. SEEK_SET means "from the start of the file" */
    if (fseek(fp, n - 1, SEEK_SET) != 0) {
        fprintf(stderr, "Error: Failed to seek in file '%s'.\n", filename);
        fclose(fp);
        return;
    }

    /* Read the character at the current offset */
    ch = fgetc(fp);

    /* Check if we hit the End Of File (meaning file is smaller than n) */
    if (ch == EOF) {
        /* Non-fatal error: Print and return to the main loop */
        fprintf(stderr, "Error: The file '%s' has fewer than %ld characters.\n", filename, n);
    } else {
        /* Success! Print the message with the ASCII value */
        printf("File '%s': The ASCII code of the %ld-th character is %d.\n", filename, n, ch);
    }

    /* Clean up memory by closing the file */
    fclose(fp);
}