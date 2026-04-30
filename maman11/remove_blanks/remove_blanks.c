/*
* Program: remove_blanks.c
* Purpose: This program receives a string of text from the user via standard
* input and processes it to remove consecutive whitespace characters
* (such as spaces, tabs and new line), condensing them into a single space.
* Then prints both the original string and the modified string to demonstrate the text processing.
* Name: Ido Sheffi
* ID: 208138974
*/
#include <stdio.h>
#include <ctype.h> /* Required for isspace() */
#include <string.h> /* For strcspn (to remove the newline) */

#define MAX_LEN 100 /* Define a reasonable maximum length as per the instructions */

/* Function Prototype */
void remove_blanks(char str[]);

int main() {
    char my_string[MAX_LEN];

    /* Request for input */
    printf("Please enter a string to process (max %d characters):\n", MAX_LEN - 1);

    /* Read input from stdin.
     * We use fgets instead of scanf("%s") because scanf stops at the first space
     */
    if (fgets(my_string, MAX_LEN, stdin) != NULL) {
        /* Remove the trailing newline if it exists */
        my_string[strcspn(my_string, "\n")] = '\0';
        /* Print the original string before modification */
        printf("\nThe Input string:\n\"%s\"\n", my_string);

        /* Call the function to modify the string */
        remove_blanks(my_string);

        /* Print the result after modification */
        printf("The string at the end of the function:\n\"%s\"\n", my_string);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}

/* The function that removes whitespace */
void remove_blanks(char str[]) {
    int read_idx = 0;
    int write_idx = 0;
    printf("The string as received by the function:\n\"%s\"\n", str);
    /* Loop until we hit the end of the original string */
    while (str[read_idx] != '\0') {

        /* isspace() checks for space (' '), tab ('\t'), and newline ('\n') */
        /* We cast to unsigned char to prevent issues with negative ASCII values */
        if (!isspace((unsigned char)str[read_idx])) {

            /* If it's NOT a whitespace, copy it to the write position */
            str[write_idx] = str[read_idx];
            write_idx++; /* Move the write index forward */
        }

        /* The read index always moves forward, no matter what */
        read_idx++;
    }

    /* Terminate the newly compacted string */
    str[write_idx] = '\0';
}