/*
* Program: turn_on.c
* Purpose: This program reads an integer from the user and turns on its 17th
* bit from the right (index 16) using bitwise operators.
* It prints the original number and the modified number in both Base 10 (decimal) and Base 2 (binary) formats.
* It also evaluates and prints a message indicating whether the value was changed or if the target bit was already on.
* Name: Ido Sheffi
* ID: 208138974
*/
#include <stdio.h>
/* Define the bit target to turn on */
#define TARGET_BIT 17
/* Function prototypes */
long turn_on(long num);
void print_binary(long num);

int main() {
    long original_num, modified_num;

    /* Request user input */
    printf("Please enter an integer number:\n");
    
    /* Read the input. %ld is the format for a long integer */
    if (scanf("%ld", &original_num) == 1) {
        
        /* Apply the bitwise operation */
        modified_num = turn_on(original_num);

        /* Print the "Before" state */
        printf("\nOriginal number in Base 10: %ld\n", original_num);
        printf("Original number in Base 2:  ");
        print_binary(original_num);
        printf("\n");

        /* Check if the value actually changed to determine our output message */
        if (original_num != modified_num) {
            printf("After turning on the %dth bit from the right: A change occurred\n", TARGET_BIT);
        } else {
            printf("The %dth bit from the right was already on, therefore no change\n", TARGET_BIT);
        }

        /* Print the "After" state */
        printf("Modified number in Base 10: %ld\n", modified_num);
        printf("Modified number in Base 2:  ");
        print_binary(modified_num);
        printf("\n");

    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

/*
 * FUNCTION: turn_on
 * PURPOSE: Turns on the 17th bit from the right without altering other bits.
 */
long turn_on(long num) {
    /* * In C, bits are zero-indexed from right to left. 
     * This means the 1st bit is index 0, so the 17th bit is index 16.
     * '1L' represents the number 1 explicitly as a long integer.
     * We subtract 1 to convert from the human-readable position (17)
     * to the zero-based index (16) required for bit shifting.
     * '<< 16' shifts that single '1' sixteen places to the left.
     * Our mask now looks like this in binary: 000...00010000000000000000
     */
    long mask = 1L << (TARGET_BIT - 1);
    
    /*
     * By OR our number with the mask, all original bits remain exactly
     * as they were except the 17th bit, which is forced to become 1.
     */
    return num | mask;
}

/*
 * FUNCTION: print_binary
 * PURPOSE: Prints a long integer in binary (Base 2) format.
 */
void print_binary(long num) {
    /* Determine exactly how many bits make up a 'long' on this specific machine.
     * sizeof(long) gives the number of bytes. Multiply by 8 to get bits.
     */
    int num_bits = sizeof(long) * 8;
    int i;
    
    /* We want to print from left to right.
     * So we loop backwards from the highest index down to 0.
     */
    for (i = num_bits - 1; i >= 0; i--) {
        
        /* Create a temporary mask with a '1' at the current bit index 'i' */
        long mask = 1L << i;
        
        /*
         * If the bit in our number at index 'i' is a 1, (num & mask) yields a non-zero value (True).
         * If the bit in our number is a 0, (num & mask) yields 0 (False).
         */
        if (num & mask) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
}